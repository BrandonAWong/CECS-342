def check_authorized(func):
    def wrapper():
        if not is_authorized():
            message = "you are not authorized"
        else:
            message = func()
        return message
    return wrapper

def is_authorized():
    return True

@check_authorized
def Do_A():
    return "Do A"

@check_authorized
def Do_B():
    return "Do B"

@check_authorized
def Do_C():
    return "Do C"

