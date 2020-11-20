import json
user = {}
with open("in.json", "r") as jsif:
    data = json.load(jsif)
for i in data:
    if i['userId'] in user.keys():
        if i['completed']:
            user[i['userId']] += 1
    else:
        if i['completed']:
            user[i['userId']] = 1
        else:
            user[i['userId']] = 0
result = []
for i in user.keys():
    result.append({"userId" : i, "task_completed" : user[i]})
with open("out.json", "w") as jsof:
    json.dump(result, jsof)