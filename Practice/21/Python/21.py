def bmi(weight:float, height:float):
    height /= 100
    return weight / (height * height)
def print_bmi(bmi:float):
    if (bmi < 18.5):
        print("Underweight")
    elif (bmi >= 18.5 and bmi < 25.0):
        print("Normal")
    elif (bmi >= 25.0 and bmi < 30.0):
        print("Overweight")
    else:
        print("Obesity")
weight,height = map(float, input().split())
print_bmi(bmi(weight, height))
