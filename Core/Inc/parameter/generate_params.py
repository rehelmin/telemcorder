#!/usr/bin/env python3
"""
Parameter Dictionary Generator using Jinja2 Templates
Generates param_dict.h from CSV/JSON using customizable templates
"""

import tomllib
import csv
from typing import List, Dict, Any
from jinja2 import Template, Environment, FileSystemLoader
import os

class ParamGenerator:
    def __init__(self, template_dir: str = "."):
        self.params = []
        self.env = Environment(loader=FileSystemLoader(template_dir))

    def load_from_toml(self, filename: str):
        """Load parameters from TOML file"""
        with open(filename, 'rb') as f:
            data = tomllib.load(f)
        
        for param in data['parameters'].items():
            self._add_param_from_dict(param)
        self.source_file = filename
    
    def _add_param_from_dict(self, param_dict: Dict[str, Any]):
        """Helper to add parameter from dictionary"""
        param_id_key = 'param_id' if 'param_id' in param_dict else 'id'
        param_id = param_dict[1][param_id_key]
        
        # Handle hex strings
        if isinstance(param_id, str) and param_id.startswith('0x'):
            param_id = int(param_id, 16)
        else:
            param_id = int(param_id)
        
        param_type = param_dict[1]['type'].lower()
        value = param_dict[1]['value']
        
        self._add_parsed_param(param_id, param_dict[0], value, param_type)
    
    def _add_parsed_param(self, param_id: int, name: str, value: Any, param_type: str):
        """Add a parsed parameter to the list"""
        type_code_map = {'int32': 0,'float': 1, 'string': 2, 'pointer': 2}
        
        # Format value for C code
        if param_type == 'int32':
            value_str = f"{{.i = {int(value)}}}"
        elif param_type == 'float':
            value_str = f"{{.f = {float(value)}f}}"
        elif param_type == 'string':
            escaped_value = str(value).replace('"', '\\"')
            value_str = f'{{.p = "{escaped_value}"}}'
        elif param_type == 'pointer':
            if str(value).upper() == 'NULL':
                value_str = "{.p = NULL}"
            else:
                value_str = f"{{.p = {value}}}"
        else:
            raise ValueError(f"Unknown type: {param_type}")
        
        self.params.append({
            'id': param_id,
            'name': name,
            'value': value,
            'value_str': value_str,
            'type': param_type,
            'type_code': type_code_map[param_type]
        })
    
    def add_param(self, param_id: int, name: str, value: Any, param_type: str):
        """Add a parameter programmatically"""
        self._add_parsed_param(param_id, name, value, param_type)
    
    def generate_header(self, output_file: str = "param_dict.h", template_file: str = "param_dict_template.h.j2"):
        """Generate the param_dict.h header file using Jinja2 template"""
        
        # Sort parameters by ID for binary search
        self.params.sort(key=lambda x: x['id'])
        
        # Add array indices after sorting
        for i, param in enumerate(self.params):
            param['array_index'] = i
        
        # Load template (required)
        if not template_file:
            raise ValueError("Template file is required")
        
        if not os.path.exists(template_file):
            raise FileNotFoundError(f"Template file not found: {template_file}")
        
        template = self.env.get_template(template_file)
        
        # Render template
        rendered = template.render(
            params=self.params,
            source_file=getattr(self, 'source_file', None)
        )
        
        # Write output
        with open(output_file, 'w') as f:
            f.write(rendered)
        
        print(f"Generated {output_file} with {len(self.params)} parameters")
        print(f"Using template: {template_file}")

def main():
    """Example usage"""
    gen = ParamGenerator()
    
    gen.load_from_toml("param_defs.toml")
    
    # Generate with custom template (required)
    # create_example_template()
    gen.generate_header("param_dict.h", "param_dict_template.h.j2")


if __name__ == "__main__":
    main()