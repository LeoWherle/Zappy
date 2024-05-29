def is_a_number(str):
    if str == "":
        return False
    try:
        int(str)
        return True
    except ValueError:
        return False
