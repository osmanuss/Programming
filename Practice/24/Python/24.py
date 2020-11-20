import json
with open('in.json', 'r') as file:
    data = json.load(file)
users = 0
for item in data:
    if item["userId"] > users:
        users = item["userId"]
complited = []
for i in range(users):
    complited.append(0)
for item in data:
    for j in range(users):
        if item["userId"] == j and item["completed"]:
            complited[j] = complited[j] + 1
new_data = []
for i in range(users):
    new_data.append("")