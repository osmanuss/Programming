from tkinter import *
import json
import requests


def weather_reload(event=None):
	r = requests.get('http://localhost:3000/raw').content.decode("UTF8")
	weather = json.loads(r)
	description.config(text=str(weather["description"]))
	temperature.config(text=str(weather["temperature"]) + "°C")


root = Tk()
root.title("Погода")
root.bind("<Button-3>", weather_reload)
root.geometry("185x220")

TopFrame = Frame(root, bg="#ffcd57")
MiddleFrame = Frame(root, bg="white")
BottomFrame = Frame(root, bg="#ffcd57", height=30)

TopFrame.pack(side=TOP, fill=X)
MiddleFrame.pack(expand=True, fill=BOTH)
BottomFrame.pack(side=BOTTOM, fill=X)

city = Label(TopFrame, font=("Franklin Gothic Medium", 12), text="Симферополь", bg="#ffcd57")
description = Label(TopFrame, font=("Georgia", 12), bg="#ffcd57")
temperature = Label(MiddleFrame, font=("Impact", 60), bg="white")

city.pack()
description.pack()
temperature.pack(expand=True)

WeatherReload()
root.mainloop()
