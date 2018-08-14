from subprocess import Popen, PIPE
import json
import pygame, random, sys, time
from pygame.locals import *
import gomoku

def quit():
    pygame.quit()
    sys.exit()

COUNTER_SIZE = 40
TILE_SIZE = 50
COUNTER_PADDING = 5
FPS = 40
BOARD_SIZE = 15
WINDOWWIDTH = TILE_SIZE * BOARD_SIZE
WINDOWHEIGHT = TILE_SIZE * BOARD_SIZE

class Engine(object):
    def __init__(self):
        super(Engine, self).__init__()
        self.resources = {}
        self.game = gomoku.Gomoku()

    def start_up(self):
        pygame.init()
        self.main_clock = pygame.time.Clock()
        self.surface = pygame.display.set_mode((WINDOWWIDTH, WINDOWHEIGHT))
        pygame.display.set_caption('Gomoku')

        font = pygame.font.SysFont(None, 48)

        self.resources['board'] = pygame.image.load('media/board.png')
        self.resources['black'] = pygame.image.load('media/black.png')
        self.resources['white'] = pygame.image.load('media/white.png')

    def new_board(self):
        the_board = pygame.Rect(0, 0, WINDOWWIDTH, WINDOWHEIGHT)
        self.surface.blit(self.resources['board'], the_board)
        pygame.display.update()

    def render(self, move):   
        x, y = move
        player = self.game.board[x][y]
        counter = pygame.Rect(x * TILE_SIZE + COUNTER_PADDING,
                              y * TILE_SIZE + COUNTER_PADDING,
                              COUNTER_SIZE, COUNTER_SIZE)
        if player == 1:
            self.surface.blit(self.resources['black'], counter)
        elif player == 2:
            self.surface.blit(self.resources['white'], counter)

        pygame.display.update()
        
    def start(self, loop_cnt, bots):
        self.start_up()
        scores = [0, 0]
        draw = 0
        while True:
            for event in pygame.event.get():
                if event.type == QUIT:
                    quit()
            turn = -1
            winner = -1
            for _ in range(loop_cnt):
                self.new_board()
                self.game.__init__()
                turn = random.randint(0, 1) if turn == -1 else 1 - winner
                print("In round {}, player {} holds the black stone.".format(_, turn+1))
                winner = self.game_loop(bots, turn)
                if winner < 0:
                    print("It is a draw.")
                    draw += 1
                else:
                    scores[winner] += 1
                    print("Winner is player {}".format(winner+1))
                    print("Now the scores are {} : {}".format(scores[0], scores[1]))  
                time.sleep(2)
                
            print('After {} games'.format(loop_cnt))
            if draw > 0:
                print('there is {} draw'.format(draw))
            for _ in range(2):
                print("player {} wins {} rounds".format(_+1, scores[_]))
                
            quit()
     
    def game_loop(self, bots, turn):
        while True:
            for event in pygame.event.get():
                if event.type == QUIT:
                    quit()
            program = bots[turn ^ (self.game.player - 1)]
            move = self.communicate(program)
            winner, stones = self.game.perform_move(move)
            self.render(move)
            if winner:
                # mark the stones
                for x, y in stones:
                    area = pygame.Rect(x * TILE_SIZE, y * TILE_SIZE,
                                          TILE_SIZE, TILE_SIZE)
                    RED = (255, 0, 0)
                    pygame.draw.rect(self.surface, RED, area, 1)
                    pygame.display.update()
                break
            self.main_clock.tick(FPS)
        return turn ^ (winner - 1)

    def communicate(self, program):
        p = Popen(program, shell=True, stdin=PIPE,
                  stdout=PIPE, universal_newlines=True)
        full_input = json.dumps({"requests": self.game.get_requests(),
                                 "responses": self.game.get_responses()
                                })
        #print('full input is {}'.format(full_input))
        output, error = p.communicate(full_input)
        #print('full output is {}'.format(output))
        response = json.loads(output)["response"]
        p.terminate()
        return response['x'], response['y']

if __name__ == '__main__':
    loop_cnt = int(sys.argv[1])
    bots = (sys.argv[2], sys.argv[3])
    commands = []
    for program in bots:
        if len(program.split('.')) < 2:
            raise Exception(
                'Unsupported file for execution {}'.format(program))
        postfix = program.split('.')[-1]
        if postfix == 'py':
            commands.append(['python', program])
        elif postfix == 'cpp' or postfix == 'c':
            program_name = program.split('.')[0]
            compile_process = Popen(['g++', program, '-std=c++17', '-O2', '-o', program_name], shell=True, stdout=PIPE)
            output, error = compile_process.communicate()
            commands.append([program_name])
        elif postfix == 'java':
            compile_process = Popen(['javac', program], shell=True, stdout=PIPE)
            output, error = compile_process.communicate()
            commands.append(['java', 'Main'])
        elif postfix == 'exe':
            commands.append([program])
        elif postfix == 'class':
            commands.append(['java', program.rstrip('.class')])
        else:
            raise Exception(
                'Unsupported file for execution {}'.format(program))
    my_engine = Engine()
    my_engine.start(loop_cnt, commands)

