class Judge:
    def __init__(self, answer: str) -> None:
        """
        Set the answer as the attribute of Judge
        answer: (int) the final answer
        """
        # TODO
        self.answer = answer

    def guess(self, num: str) -> bool:
        """
        Method that guess the number, it'll print info that shows:
            Your guess is ...; the result is xAxB
            e.g.: Your guess is 0123; the result is 0A1B
        num: the number that it guessed
        return: whether the player guess the correct answer
        """
        # TODO
        numA = 0
        numB = 0
        for i in range(len(num)):
            if num[i] == self.answer[i]:
                numA += 1

        for i in range(len(num)):
            for j in range(len(num)):
                if num[i] == self.answer[j]:
                    numB += 1

        numB -= numA

        print("Your guess is " + num + "; the result is " +
              str(numA) + "A" + str(numB) + "B")
        if numA == len(num) and numB == 0:
            return True
        else:
            return False


def read_input(guess_len: int) -> str:
    """
    Function that read player's guess.
    guess_len: length the the player should guess. it would be same as the length of answer
    return: the valid string guessed by player

    You should show the hint message:
        "Enter your guess:\n"
    If the player's guess is invalid, you should print:
        "Invalid, please enter your guess again:\n"
    Note: a valid guess means contain only guess_len non-repetitive integer range from 0~9
    """
    # TODO
    player_guess = str(input("Enter your guess:\n"))
    valid = bool(player_guess.isnumeric()) and guess_len == len(player_guess)

    if valid == False:
        pass
    else:
        count = [int(x) for x in player_guess]
        res = [0 for i in range(10)]

        for i in count:
            res[i] += 1

        for i in range(0, 10):
            if res[i] > 1:
                valid = False
                break

    while valid == False:
        player_guess = str(input("Invalid, please enter your guess again:\n"))
        valid = bool(player_guess.isnumeric()
                     ) and guess_len == len(player_guess)
        if valid == False:
            pass
        else:
            count = [int(x) for x in player_guess]
            res = [0 for i in range(10)]

            for i in count:
                res[i] += 1

            for i in range(0, 10):
                if res[i] > 1:
                    valid = False
                    break

    return player_guess


def enter_answer() -> str:
    """
    Function that enter the answer, you can assume that the answer must be valid.
    """
    # TODO
    ans = str(input())
    return ans
