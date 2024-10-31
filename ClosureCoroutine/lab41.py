from datetime import datetime

def check_authorized(func):
    def wrapper():
        # 7AM - 10PM
        if not (7 <= datetime.now().hour <= 22):
            return "It is currently not day."
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

print(Do_A(), Do_B(), Do_C(), sep="\n")
