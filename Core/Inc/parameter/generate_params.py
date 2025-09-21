#!/usr/bin/env python3
"""
Parameter Dictionary Generator using Jinja2 Templates
Generates param_dict.h from CSV/JSON using customizable templates
"""

import json
import csv
from typing import List, Dict, Any
from jinja2 import Template, Environment, FileSystemLoader
import os

class ParamGenerator:
    def __init__(self, template_dir: str = "."):
        self.params = []
        self.env = Environment(loader=FileSystemLoader(template_dir))
    
    def load_from_csv(self, filename: str):
        """Load parameters from CSV file with columns: param_id,name,value,type"""
        with open(filename, 'r') as f:
            reader = csv.DictReader(f)
            for row in reader:
                self._add_param_from_dict(row)
        self.source_file = filename
    
    def load_from_json(self, filename: str):
        """Load parameters from JSON file"""
        with open(filename, 'r') as f:
            data = json.load(f)
        
        for param in data['parameters']:
            self._add_param_from_dict(param)
        self.source_file = filename
    
    def _add_param_from_dict(self, param_dict: Dict[str, Any]):
        """Helper to add parameter from dictionary"""
        param_id_key = 'param_id' if 'param_id' in param_dict else 'id'
        param_id = param_dict[param_id_key]
        
        # Handle hex strings
        if isinstance(param_id, str) and param_id.startswith('0x'):
            param_id = int(param_id, 16)
        else:
            param_id = int(param_id)
        
        param_type = param_dict['type'].lower()
        value = param_dict['value']
        
        self._add_parsed_param(param_id, param_dict['name'], value, param_type)
    
    def _add_parsed_param(self, param_id: int, name: str, value: Any, param_type: str):
        """Add a parsed parameter to the list"""
        type_code_map = {'int32': 0, 'float': 1, 'string': 2, 'pointer': 2}
        
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
    
    # Add parameters programmatically
    gen.add_param(0x0001, "system_version", 100, "int32")
    gen.add_param(0x0010, "motor_speed", 1500.0, "float")
    gen.add_param(0x0020, "sensor_offset", -25, "int32")
    gen.add_param(0x0030, "calibration_data", "NULL", "pointer")
    gen.add_param(0x0040, "max_temperature", 85.5, "float")
    gen.add_param(0x0050, "device_name", "STM32_Device", "string")
    gen.add_param(0x0100, "control_mode", 2, "int32")
    gen.add_param(0x0200, "pid_kp", 0.8, "float")
    gen.add_param(0x0201, "pid_ki", 0.1, "float")
    gen.add_param(0x0202, "pid_kd", 0.05, "float")
    
    # Generate with custom template (required)
    # create_example_template()
    gen.generate_header("param_dict.h", "param_dict_template.h.j2")
    
    print("\nTo use with CSV:")
    print("gen.load_from_csv('params.csv')")
    print("gen.generate_header()")
    
    print("\nTo install Jinja2:")
    print("pip install jinja2")


if __name__ == "__main__":
    main()