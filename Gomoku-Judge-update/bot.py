import json
import random
BOARD_SIZE = 15
board = [[0 for x in range(BOARD_SIZE)] for y in range(BOARD_SIZE)]

def place_at(x, y):
    if x >= 0 and y >= 0:
        board[x][y] = 1

def random_available_position():
    all_moves = list()
    for i in range(BOARD_SIZE):
        for j in range(BOARD_SIZE):
            if board[i][j] == 0:
                all_moves.append((i, j))
    x, y = random.choice(all_moves)
    return {'x': x, 'y': y}

if __name__ == "__main__":
    # 解析读入的JSON
    full_input = json.loads(input())
    if "data" in full_input:
        my_data = full_input["data"]; # 该对局中，上回合该Bot运行时存储的信息
    else:
        my_data = None

    # 分析自己收到的输入和自己过往的输出，并恢复状态
    all_requests = full_input["requests"]
    all_responses = full_input["responses"]

    for i in range(len(all_responses)):
        my_input = all_requests[i] # i回合我的输入
        my_output = all_responses[i] # i回合我的输出
        # TODO: 根据规则，处理这些输入输出，从而逐渐恢复状态到当前回合
        place_at(my_input['x'], my_input['y'])
        place_at(my_output['x'], my_output['y'])

    # 看看自己最新一回合输入
    curr_input = all_requests[-1]
    place_at(curr_input['x'], curr_input['y'])

    # TODO: 作出决策并输出
    my_action = random_available_position()

    print(json.dumps({
        "response": my_action
    }))
