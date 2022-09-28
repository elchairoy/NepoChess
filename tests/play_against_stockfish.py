from pickle import TRUE
from re import T
import pexpect
import stockfish
from os import system
from sys import exit
import numpy
import random
from decimal import Decimal

# A lot of functions get argument nepo (which nepo is the action for), It's only used for when it's nepo against itself.

NEPOCHESS_BIN_PATH = './bin/runtests'
NEPOCHESS2_BIN_PATH = './bin/runtests2'

sf = 0
nepo_chess = 0
nepo_chess2 = 0
TIMEOUT = 1000

NEPOCHESS_ELO = 600
     
def get_sf_move():
    move = sf.get_best_move()
    # print(f'[+] Stockfish move is {move}')
    sf.make_moves_from_current_position([move])
    return move

def send_sf_move(move):
    # print(f'[+] Sending {move} to stockfish')
    sf.make_moves_from_current_position([move])

def get_nepo_move(nepo = nepo_chess):
    result = nepo.expect(['[a-h][1-8][a-h][1-8][q,r,b,n]?', 'CHECKMATE 1-0', 'STALMATE 0.5-0.5'], timeout=TIMEOUT)
    if result == 1:
        print('CHECKMATE, STOCKFISH WON')
        return 0
    elif result == 2:
        print('STALMATE')
        return 0.5

    move = nepo.after.decode()
    # print(f'[+] Nepo move is {move}')
    return move

def send_nepo_move(move, nepo = nepo_chess):
    promotion_dict = {
        'q': '0',
        'r': '1',
        'n': '2',
        'b': '3'
    }

    result = nepo.expect(["enter src: ", 'CHECKMATE 0-1', 'STALMATE 0.5-0.5'],timeout=TIMEOUT)
    if result == 1:
        print('CHECKMATE, NEPO WON')
        return 1
    elif result == 2:
        print('STALMATE')
        return 0.5

    nepo.sendline(move[:2])
    nepo.expect("enter dst:")
    nepo.sendline(move[2:4])
    if len(move) == 5: # Promotion
        nepo.expect("promot to\? \(0=Q,1=R,2=N,3=B\): ")
        nepo.sendline(promotion_dict[move[4]])

# Expects to get a board from nepo
def print_board(nepo = nepo_chess,if_to_print = True):
    system("clear")
    nepo.expect('  -(?s).*h')
    board = nepo.after.decode()
    if (if_to_print): print(board)
    
def play_game_against_stockfish(level):
    global sf, nepo_chess
    sf = stockfish.Stockfish('/usr/local/bin/stockfish')
    sf.update_engine_parameters({"UCI_LimitStrength":"true","Skill Level":level})
    nepo_chess = pexpect.spawn(NEPOCHESS_BIN_PATH)
    while True:
        print_board(nepo_chess)
        print("STOCKFISH IS THINKING...")
        sf_move = get_sf_move()
        status = send_nepo_move(sf_move,nepo_chess)
        if status is not None:
            return status
        print_board(nepo_chess)
        
        print("NEPO IS THINKING...")
        nepo_move = get_nepo_move(nepo_chess)
        if type(nepo_move) != str:
            return nepo_move
        send_sf_move(nepo_move)

# Make nepo play against itself
def play_game_against_itself():
    global nepo_chess, nepo_chess2
    nepo_chess = pexpect.spawn(NEPOCHESS_BIN_PATH)
    nepo_chess2 = pexpect.spawn(NEPOCHESS2_BIN_PATH)
    while True:
        print_board(nepo_chess2,True)
        
        print("NEPO 1 IS THINKING...")
        nepo1_move = get_nepo_move(nepo_chess)
        status = send_nepo_move(nepo1_move,nepo_chess2)
        if status is not None:
            return status
        
        print_board(nepo_chess,True)
        
        print("NEPO 2 IS THINKING...")
        nepo2_move = get_nepo_move(nepo_chess2)
        print("got:\n"+nepo2_move)
        status = send_nepo_move(nepo2_move,nepo_chess)
        if status is not None:
            return status

# Estimates the strength of NepoChess against stockfish
def estimate_strength():
    strength = 12   
    for level in range(21):
        if (play_game_against_stockfish(strength)):
            strength += 1
    return strength

print(estimate_strength())


'''
23.9.22:  NepoChess is at level 0







'''