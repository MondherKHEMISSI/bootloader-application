import os
import re

def parse_header_file(file_path):
    with open(file_path, 'r') as file:
        content = file.read()
        typedef_enum_pattern = r'typedef\s+enum\s*{([^}]*)}[^;]*;'
        typedef_enum_match = re.search(typedef_enum_pattern, content, re.DOTALL)

        if typedef_enum_match:
            #print("Found typedef enum:")
            enum_values = typedef_enum_match.group(1).strip().split(',')
            enum_values_dict = {}

            value = 0
            for enum_value in enum_values:
                enum_value = enum_value.strip().split('=')
                if len(enum_value) == 1:
                    enum_name = enum_value[0].strip()
                    enum_values_dict[enum_name] = value
                    value += 1
                else:
                    enum_name = enum_value[0].strip()
                    enum_val = int(enum_value[1].strip())
                    enum_values_dict[enum_name] = enum_val
                    value = enum_val + 1
            '''
            for key, val in enum_values_dict.items():
                print(f"{key} = {val}")
            '''
            return enum_values_dict
        else:
            print("No typedef enum found in the file.")
            return None

def extract_module_name(enum_name):
    # Search for the entire module name that contains 'bb' in a case-insensitive manner
    match = re.search(r'(?i)(bb\w*)', enum_name)
    
    if match:
        # If a match is found, return the matched module name
        return match.group(1)
    else:
        # If no match is found, return None
        return None

def find_header_file(project_path, target_file_name):
    target_file_lower = (target_file_name + ".h").lower()
    for root, dirs, files in os.walk(project_path):
        for file in files:
            if file.lower() == target_file_lower:
                return os.path.join(root, file)
    return None

# Specify the project directory and the header file to search for
project_path = '.'
header_file_name = 'logger_api'
file_path = find_header_file(project_path, header_file_name)
enum_values = parse_header_file(file_path)
enums_mapping = {}
if enum_values:
    for enum_name, value in enum_values.items():
        module_name = extract_module_name(enum_name)
        if module_name:
            #print(f"Extracted module name for {enum_name}: {module_name}")
            file_path = find_header_file(project_path, module_name)
            #print(file_path)
            if file_path:
                enums_mapping[value] = parse_header_file(file_path)
        else:
            print(f"Module name not found in the enum {enum_name}.")

print(enums_mapping)