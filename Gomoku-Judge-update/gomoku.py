import json
BOARD_SIZE = 15

class Gomoku(object):
    def __init__(self):
        super(Gomoku, self).__init__()
        self.player = 1
        self.board = [[0 for x in range(BOARD_SIZE)] for y in range(BOARD_SIZE)]
        self.requests = [list(), list()]
        self.responses = [list(), list()]
        self.requests[0].append({"x":-1, "y":-1})

    def get_requests(self):
        return self.requests[self.player-1]

    def get_responses(self):
        return self.responses[self.player-1]

    def perform_move(self, move):
        x, y = move
        if self.board[x][y] != 0:
            raise Exception("Illegal move at {}, {}".format(x, y))
        self.board[x][y] = self.player
        
        my_action = {"x": x, "y": y}
        self.responses[self.player-1].append(my_action)
        self.requests[2-self.player].append(my_action)
        
        stones = self.check_winner(x, y)
        if stones:
            return self.player, stones
        
        if self.board_full():
            return 0, []

        self.player = 3 - self.player
        return None, None

    def board_full(self):
        return all(self.board[x][y] != 0 for x in range(BOARD_SIZE) for y in range(BOARD_SIZE))
    
    def check_winner(self, x, y):
        for direction in ((0,1),(1,-1),(1,0),(1,1)):
            stones = [(x, y)]
            for i in (-1, 1):
                for j in range(1, 5):
                    row = x + i * j * direction[0]
                    col = y + i * j * direction[1]
                    if row < 0 or row > BOARD_SIZE - 1 or col < 0 or col > BOARD_SIZE - 1:
                        break
                    if self.board[row][col] == self.board[x][y]:
                        stones.append((row, col))
                    else:
                        break
            if len(stones) >= 5:
                return stones
        return
            
        
        
