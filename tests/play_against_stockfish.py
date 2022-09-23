import pexpect
import stockfish
from os import system
from sys import exit
import numpy
import random
from decimal import Decimal

NEPOCHESS_BIN_PATH = './bin/runtests'

sf = 0
nepo_chess = 0
TIMEOUT = 1000

NEPOCHESS_ELO = 600

def play_game(elo):
     ka = (1/(1+(10)**(Decimal((elo-NEPOCHESS_ELO)/400))))
     result = numpy.random.choice([0,1], p=[1-ka,ka])
     return result
     
def get_sf_move():
    move = sf.get_best_move()
    # print(f'[+] Stockfish move is {move}')
    sf.make_moves_from_current_position([move])
    return move

def send_sf_move(move):
    # print(f'[+] Sending {move} to stockfish')
    sf.make_moves_from_current_position([move])

def get_nepo_move():
    result = nepo_chess.expect(['[a-h][1-8][a-h][1-8][q,r,b,n]?', 'CHECKMATE 1-0', 'STALMATE 0.5-0.5'], timeout=TIMEOUT)
    if result == 1:
        print('CHECKMATE, STOCKFISH WON')
        return 0
    elif result == 2:
        print('STALMATE')
        return 0.5

    move = nepo_chess.after.decode()
    # print(f'[+] Nepo move is {move}')
    return move

def send_nepo_move(move):
    promotion_dict = {
        'q': '0',
        'r': '1',
        'n': '2',
        'b': '3'
    }

    # print(f'[+] Sending {"".join(move)} to nepo')
    result = nepo_chess.expect(["enter src: ", 'CHECKMATE 0-1', 'STALMATE 0.5-0.5'],timeout=TIMEOUT)
    if result == 1:
        print('CHECKMATE, NEPO WON')
        return 1
    elif result == 2:
        print('STALMATE')
        return 0.5

    nepo_chess.sendline(move[:2])
    nepo_chess.expect("enter dst:")
    nepo_chess.sendline(move[2:4])
    if len(move) == 5: # Promotion
        nepo_chess.expect("promot to\? \(0=Q,1=R,2=N,3=B\): ")
        nepo_chess.sendline(promotion_dict[move[4]])

def print_board():
    system("clear")
    nepo_chess.expect('  -(?s).*h')
    print(nepo_chess.after.decode())
    
def play_game(level):
    global sf, nepo_chess
    sf = stockfish.Stockfish('/usr/local/bin/stockfish')
    sf.update_engine_parameters({"UCI_LimitStrength":"true","Skill Level":level})
    nepo_chess = pexpect.spawn(NEPOCHESS_BIN_PATH)
    while True:
        print_board()
        print("STOCKFISH IS THINKING...")
        sf_move = get_sf_move()
        status = send_nepo_move(sf_move)
        if status is not None:
            return status
        print_board()
        
        print("NEPO IS THINKING...")
        nepo_move = get_nepo_move()
        if type(nepo_move) != str:
            return nepo_move
        send_sf_move(nepo_move)

def estimate_elo1(current_elo):
    games = 0     
    for level in range(8):
        elo = 800 + 100*level
        ka = (1/(1+(10)**(Decimal((elo-current_elo)/400))))
        for _ in range(1):
            games+=1
            current_elo += 80*(play_game(level) - ka)
            ka = (1/(1+(10)**(Decimal((elo-current_elo)/400))))
    return current_elo
#print(estimate_elo1(NEPOCHESS_ELO))
print(play_game(0))