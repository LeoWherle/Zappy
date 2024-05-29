"""
This is the tools module. It contains utility functions that can be used throughout the application.
"""

def is_a_number(input_str):
    """
    This function checks if the given string can be converted to an integer.

    Parameters:
    input_str (str): The string to check.

    Returns:
    bool: True if the string can be converted to an integer, False otherwise.
    """
    if input_str == "":
        return False
    try:
        int(input_str)
        return True
    except ValueError:
        return False
