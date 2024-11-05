digits = "23"

bank = [["a","b","c"],["d","e","f"],["g","h","i"],["j","k","l"],["m","n","o"],["p","q","r","s"],["t","u","v"],["w","x","y","z"]]

if len(digits) == 0:
    print([])

outputs = []
builder_instructions = []        

for x in digits:
    builder_instructions.append(0)
    builder_instructions.append(len(bank[int(x) - 2]))
    
choices = builder_instructions[1::2]
total_strings = 1
for x in choices:
    total_strings *= x

builder_modifier = -2
for x in range(total_strings):
    s = ""
    i = 0
    for y in digits:
        s = s + bank[int(y) - 2][builder_instructions[i]]
        i += 2
    outputs.append(s)
    if builder_instructions[builder_modifier] + 1 < builder_instructions[builder_modifier + 1]:
        builder_instructions[builder_modifier] += 1
    else:
        while builder_instructions[builder_modifier] + 1 == builder_instructions[builder_modifier + 1]:
            builder_instructions[builder_modifier] = 0
            builder_modifier -= 2
            if builder_modifier < 0:
                break
        builder_modifier = -2
    
    

print(outputs)