import argparse, os

# This script generate a base for a source or header file

start_comment = "/*-----"
end_comment = "-----*/"

def get_description(text):
    return f"""/*
* {text}
* 
* Description
*
* Author : CAPITANO Giuliano (@Rav3nPho3nix)
*/

"""

def get_section(section, content):
    return f"""{start_comment} {section} {end_comment}
{content}
{start_comment}{end_comment}

"""

# Class for a dictionary, if the key is missing, always give the same default one
class dict_(dict):
    def __missing__(self, key):
        return self["_"]

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate a C source or header file")

    parser.add_argument('filename')
    parser.add_argument('extension')
    parser.add_argument('path')

    args = parser.parse_args()

    print(f"{os.getcwd()}/{args.path}")

    source_sections = ["Includes", "Defines", "Global variables", "Internal functions", "Function implementations"]
    header_sections = ["Include guards", "Includes", "Defines", "Typedefs, structs and enums", "Function signatures", "End of include guards"]

    # Dictionary to pre-fill the includes guards
    sections_content = dict_({
        "Include guards":"#ifndef NAME_H\n#define NAME_H",
        "End of include guards":"#endif",
        "_":""})

    # Select the sections for .c or .h file
    if args.extension == "c":
        sections = source_sections
    elif args.extension == "h":
        sections = header_sections
    else :
        print("File extension must be 'c' or 'h'")
        exit()

    # Complete the file content
    file_content = get_description(f"{args.filename}.{args.extension}")
    for section in sections:
        file_content += get_section(section, sections_content[section])
    # Remove the last 2 characters
    file_content = file_content[:-2]

    # Open and fill file
    with open(f"{os.getcwd()}/{args.path}/{args.filename}.{args.extension}", "w") as file:
        file.write(file_content)