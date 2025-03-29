'''
Simple example pokerbot, written in Python.
'''
from skeleton.actions import FoldAction, CallAction, CheckAction, RaiseAction
from skeleton.states import GameState, TerminalState, RoundState
from skeleton.states import NUM_ROUNDS, STARTING_STACK, BIG_BLIND, SMALL_BLIND
from skeleton.bot import Bot
from skeleton.runner import parse_args, run_bot

import random
import math


class Player(Bot):
    '''
    A pokerbot.
    '''

    def __init__(self):
        '''
        Called when a new game starts. Called exactly once.

        Arguments:
        Nothing.

        Returns:
        Nothing.
        '''
        pass

    def handle_new_round(self, game_state, round_state, active):
        '''
        Called when a new round starts. Called NUM_ROUNDS times.

        Arguments:
        game_state: the GameState object.
        round_state: the RoundState object.
        active: your player's index.

        Returns:
        Nothing.
        '''
        #my_bankroll = game_state.bankroll  # the total number of chips you've gained or lost from the beginning of the game to the start of this round
        #game_clock = game_state.game_clock  # the total number of seconds your bot has left to play this game
        #round_num = game_state.round_num  # the round number from 1 to NUM_ROUNDS
        #my_cards = round_state.hands[active]  # your cards
        #big_blind = bool(active)  # True if you are the big blind
        pass

    def handle_round_over(self, game_state, terminal_state, active):
        '''
        Called when a round ends. Called NUM_ROUNDS times.

        Arguments:
        game_state: the GameState object.
        terminal_state: the TerminalState object.
        active: your player's index.

        Returns:
        Nothing.
        '''
        #my_delta = terminal_state.deltas[active]  # your bankroll change from this round
        previous_state = terminal_state.previous_state  # RoundState before payoffs
        #street = previous_state.street  # 0, 3, 4, or 5 representing when this round ended
        #my_cards = previous_state.hands[active]  # your cards
        #opp_cards = previous_state.hands[1-active]  # opponent's cards or [] if not revealed
        pass

    # def chance_of_high_card(my_cards, community_cards): #returns array, [<prob of 1>, <prob of 2>, <prob of 3>]
    #     #format 
    #     cards_in_deck = 52 - len(my_cards) - len(community_cards)
    #     probabilities = []

    #     return probabilities


    # def chance_of_high_card_opponent(my_cards, community_cards):
    #     cards_in_deck = 52 - len(my_cards) - len(community_cards)
    #     probabilities = []
    #     return probabilities

    def n_choose_k(self,n,k):
        return (math.factorial(n)) / (math.factorial(n-k) * math.factorial(k))
    
    def probability_info(self, known_cards, unknown_cards_num):
        #assumed to be in form ["8c", "4h"], etc
        cards_in_deck = 52 - len(known_cards)
        num_cards = [0] * 15
        probabilities = [0.0] * 15
        number_left = [4] * 15
        num_suits = [13] * 4 #a,c,h,s
        

        for card in known_cards:
            rank = card[0]
            suit = card[1]
            # Convert face cards to numbers
            if rank == 'T':
                rank_num = 10
            elif rank == 'J':
                rank_num = 11
            elif rank == 'Q':
                rank_num = 12
            elif rank == 'K':
                rank_num = 13
            elif rank == 'A':
                rank_num = 14
            else:
                rank_num = int(rank)

            if suit == 'a':
                num_suits[0] -= 1
            elif suit == 'c':
                num_suits[1] -= 1
            elif suit == 'h':
                num_suits[2] -= 1 
            elif suit == 's':
                num_suits[3] -= 1


                
            num_cards[rank] += 1
            number_left[rank] -= 1
        return {"cards_in_deck": cards_in_deck,
                "num_cards": num_cards,
                "probabilities": probabilities,
                "number_left": number_left,
                "num_suits": num_suits}
    
    # def chance_of_pair(self, known_cards, unknown_cards_num): #returns array, [<prob of 1>, <prob of 2>, <prob of 3>]
    #     #assumed to be in form ["8c", "4h"], etc

    #     info = self.probability_info(self, known_cards, unknown_cards_num)
    
    #     cards_in_deck = info["cards_in_deck"]
    #     num_cards = info["num_cards"]
    #     probabilities = info["probabilities"]
    #     number_left = info["number_left"]
        
    #     for i in range(2,15):
    #         if(num_cards[i] == 2):
    #             probabilities[i] = 1.0
    #             continue
    #         elif(num_cards[i] == 1):
    #             all_scenarios = self.n_choose_k(cards_in_deck, unknown_cards_num)
    #             choose_1 = self.n_choose_k(unknown_cards_num, 1)
    #             dont_choose_2 = self.n_choose_k(cards_in_deck - unknown_cards_num, 2)
    #             probability = (choose_1 * dont_choose_2) / all_scenarios
    #             probabilities[i] = probability
    #         elif(num_cards[i] == 0):
    #             all_scenarios = self.n_choose_k(cards_in_deck, unknown_cards_num)
    #             choose_2 = self.n_choose_k(unknown_cards_num, 2)
    #             dont_choose_2 = self.n_choose_k(cards_in_deck - unknown_cards_num, 2)
    #             probability = (choose_2 * dont_choose_2) / all_scenarios
    #             probabilities[i] = probability

    #     return probabilities
    
    def chance_of_n_pair(self, known_cards, unknown_cards_num, n):
        info = self.probability_info(self, known_cards, unknown_cards_num)
    
        cards_in_deck = info["cards_in_deck"]
        num_cards = info["num_cards"]
        probabilities = info["probabilities"]
        unknown_cards_used_arr = [0] * 15

        dont_choose = self.n_choose_k(cards_in_deck - unknown_cards_num, 4-n)
        all_scenarios = self.n_choose_k(cards_in_deck, unknown_cards_num)
        
        for i in range(2,15):
            if(num_cards[i] >= n):
                probabilities[i] = 1.0 #do we have to account for the chance u get a 4-pair? 
                unknown_cards_used_arr[i] = 0
                continue
            choose = self.n_choose_k(unknown_cards_num, n-num_cards[i])
            probability = (choose * dont_choose) / all_scenarios 
            unknown_cards_used = n-num_cards[i]
            probabilities[i] = probability
            unknown_cards_used_arr[i] = unknown_cards_used

        return probabilities, unknown_cards_used_arr
    
    def chance_of_double_pair(self, known_cards, unknown_cards_num):
        info = self.probability_info(self, known_cards, unknown_cards_num)
    
        cards_in_deck = info["cards_in_deck"]
        num_cards = info["num_cards"]
        probabilities = info["probabilities"]

        chance_of_first_pair, unknown_cards_used_arr = self.chance_of_n_pair(self, known_cards, unknown_cards_num, 2)

        for i in range(2, 15):
            for j in range(i+1, 15):
                unknown_cards_num_left = unknown_cards_num - unknown_cards_used_arr[i]
                chance_of_second_pair = self.chance_of_n_pair(self, known_cards, unknown_cards_num_left, 2)
                if(i == j):
                    continue
                probabilities[j] += chance_of_first_pair[i] * chance_of_second_pair[j]

        return probabilities
    
    def chance_of_full_house(self, known_cards, unknown_cards_num):
        info = self.probability_info(self, known_cards, unknown_cards_num)
    
        cards_in_deck = info["cards_in_deck"]
        num_cards = info["num_cards"]
        probabilities = info["probabilities"]

        chance_of_pair, unknown_cards_used_arr = self.chance_of_n_pair(self, known_cards, unknown_cards_num, 2)

        for i in range(2, 15):
            for j in range(i+1, 15):
                unknown_cards_num_left = unknown_cards_num - unknown_cards_used_arr[i]
                chance_of_three_of_a_kind = self.chance_of_n_pair(self, known_cards, unknown_cards_num_left, 3)
                if(i == j):
                    continue
                probabilities[j] += chance_of_pair[i] * chance_of_three_of_a_kind[j]

        return probabilities
    
    def chance_of_straight(self, known_cards, unknown_cards_num):
        info = self.probability_info(self, known_cards, unknown_cards_num)
    
        cards_in_deck = info["cards_in_deck"]
        num_cards = info["num_cards"]
        probabilities = info["probabilities"] #0-10, based on where it starts

        all_scenarios = self.n_choose_k(cards_in_deck, unknown_cards_num)

        for i in range(1,11):
            needed = 5
            for j in range(i, i+5):
                if(num_cards[j] >= 1):
                    needed -= 1
            leftover_deck = cards_in_deck - needed 
            not_needed_num = unknown_cards_num - needed
            ways_to_arrange_leftover = self.n_choose_k(leftover_deck, not_needed_num)

            probability = (4 ** needed * ways_to_arrange_leftover) / all_scenarios
            probabilities[i] = probability

        return probabilities

    def chance_of_flush(self, known_cards, unknown_cards_num):
        info = self.probability_info(self, known_cards, unknown_cards_num)
    
        cards_in_deck = info["cards_in_deck"] # cards not known or unknown, simply not dealt
        num_cards = info["num_cards"] #array of freq of each card in known
        probabilities = info["probabilities"] #indicies 0-3, based on which suit
        num_suits = info["num_suits"]

        all_scenarios = self.n_choose_k(cards_in_deck, unknown_cards_num)

        #["a","c","h","s"]
        for i in range(0,4):
            suit_num = num_suits[i]
            total = 0
            num_found = 13 - suit_num
            needed = 5 - num_found
            for k in range(needed, unknown_cards_num+1):
                possible_flushes = self.n_choose_k(suit_num, k)
                not_used_unknown = unknown_cards_num-k
                leftover_cards = cards_in_deck
                possible_other_cards = self.n_choose_k(leftover_cards, not_used_unknown)
                total += possible_flushes * possible_other_cards
            probability = total / all_scenarios
            probabilities[i] = probability

        return probabilities[i]
    

    def get_action(self, game_state, round_state, active):
        '''
        Where the magic happens - your code should implement this function.
        Called any time the engine needs an action from your bot.

        Arguments:
        game_state: the GameState object.
        round_state: the RoundState object.
        active: your player's index.

        Returns:
        Your action.
        '''
        legal_actions = round_state.legal_actions()  # the actions you are allowed to take
        street = round_state.street  # 0, 3, 4, or 5 representing pre-flop, flop, turn, or river respectively
        my_cards = round_state.hands[active]  # your cards
        board_cards = round_state.deck[:street]  # the board cards

        my_known_cards = my_cards + board_cards
        my_unknown_cards = (4 - len(board_cards))

        my_chance_of_1_pair = self.chance_of_n_pair(my_known_cards, my_unknown_cards, 2)
        my_chance_of_3_of_a_kind = self.chance_of_n_pair(my_known_cards, my_unknown_cards, 3)
        my_chance_of_4_of_a_kind = self.chance_of_n_pair(my_known_cards, my_unknown_cards, 4)
        my_chance_of_double_pair = self.chance_of_double_pair(my_known_cards, my_unknown_cards)
        my_chance_of_full_house = self.chance_of_full_house(my_known_cards, my_unknown_cards)
        my_chance_of_straight = self.chance_of_straight(my_known_cards, my_unknown_cards)
        my_chance_of_flush = self.chance_of_flush(my_known_cards, my_unknown_cards)

        print(total_sum = sum(
    my_chance_of_1_pair +
    my_chance_of_3_of_a_kind +
    my_chance_of_4_of_a_kind +
    my_chance_of_double_pair +
    my_chance_of_full_house +
    my_chance_of_straight +
    my_chance_of_flush
)
)

        opp_known_cards = board_cards
        opp_unknown_cards = 3 + (4 - len(board_cards))

        opp_chance_of_1_pair = self.chance_of_n_pair(opp_known_cards, opp_unknown_cards, 2)
        opp_chance_of_3_of_a_kind = self.chance_of_n_pair(opp_known_cards, opp_unknown_cards, 3)
        opp_chance_of_4_of_a_kind = self.chance_of_n_pair(opp_known_cards, opp_unknown_cards, 4)
        opp_chance_of_double_pair = self.chance_of_double_pair(opp_known_cards, opp_unknown_cards)
        opp_chance_of_full_house = self.chance_of_full_house(opp_known_cards, opp_unknown_cards)
        opp_chance_of_straight = self.chance_of_straight(opp_known_cards, opp_unknown_cards)
        opp_chance_of_flush = self.chance_of_flush(opp_known_cards, opp_unknown_cards)

        print(total_sum = sum(
    my_chance_of_1_pair +
    my_chance_of_3_of_a_kind +
    my_chance_of_4_of_a_kind +
    my_chance_of_double_pair +
    my_chance_of_full_house +
    my_chance_of_straight +
    my_chance_of_flush
)
)
        
        my_pip = round_state.pips[active]  # the number of chips you have contributed to the pot this round of betting
        opp_pip = round_state.pips[1-active]  # the number of chips your opponent has contributed to the pot this round of betting
        my_stack = round_state.stacks[active]  # the number of chips you have remaining
        opp_stack = round_state.stacks[1-active]  # the number of chips your opponent has remaining
        continue_cost = opp_pip - my_pip  # the number of chips needed to stay in the pot
        my_contribution = STARTING_STACK - my_stack  # the number of chips you have contributed to the pot
        opp_contribution = STARTING_STACK - opp_stack  # the number of chips your opponent has contributed to the pot

        if RaiseAction in legal_actions:
           min_raise, max_raise = round_state.raise_bounds()  # the smallest and largest numbers of chips for a legal bet/raise
           min_cost = min_raise - my_pip  # the cost of a minimum bet/raise
           max_cost = max_raise - my_pip  # the cost of a maximum bet/raise
        if RaiseAction in legal_actions:
            if random.random() < 0.5:
                return RaiseAction(min_raise)
        if CheckAction in legal_actions:  # check-call
            return CheckAction()
        if random.random() < 0.25:
            return FoldAction()
        return CallAction()  # If we can't raise, call if possible
    

    def high_card(self, game_state, round_state, active):
        #my_bankroll = game_state.bankroll  # the total number of chips you've gained or lost from the beginning of the game to the start of this round
        #game_clock = game_state.game_clock  # the total number of seconds your bot has left to play this game
        #round_num = game_state.round_num  # the round number from 1 to NUM_ROUNDS
        #my_cards = round_state.hands[active]  # your cards
        #big_blind = bool(active)  # True if you are the big blind

        # game_state: the GameState object.
        # round_state: the RoundState object.
        # active: your player's index.

        return