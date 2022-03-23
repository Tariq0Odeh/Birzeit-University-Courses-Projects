from game import Sudoku
from time import time
class MultyPlayer(Sudoku):
    # We have 2 players in this mode
    Players = [0, 0]
    Turns = ["Player 1", "Player 2"]
    Times = [0, 0]
    def __init__(self, GameLoaded, Difficulty, FileName):
        super().__init__(GameLoaded, Difficulty=Difficulty, FileName=FileName)

    # This function is used when choosing to play the MultyPlayer method
    def play(self):
        turn = 0
        SeqPasses = 0
        while not self.Solved():
            self.print_Board(self.getBoard())
            print(self.Turns[turn] +" Turn")
            t1 = time()
            choice = 0
            try:
                choice = int(input("1- Fill 2- Pass 3- Solve 4- Exit the game\n"))
            except:
                pass

            if choice == 1: # if user select fill optio
                SeqPasses = 0
                data = tuple(input("You must enter the data like: row column number\n").split(' '))
                print(data)
                previous = self.getBoard()[int(data[0])-1][int(data[1])-1]

                if self.valid(int(data[0])-1, int(data[1])-1, int(data[2])):
                    self.setBoard(int(data[0])-1, int(data[1])-1,  int(data[2]))
                    if int(data[2] != 0) and previous == 0:
                        self.Players[turn]+=1

                    
                else:
                    
                    print("Invalid! "+self.Turns[turn]+" score will be reduced by 1 !")
                    self.Players[turn]-=1
                t2 = time()
                self.Times[turn] += (t2-t1)
                turn = not turn

            elif choice == 2: # if user select pass option
                
                self.Players[turn]-=1
                print(self.Turns[turn]+" score will be reduced by 1 !")

                SeqPasses += 1
                if SeqPasses == 4:
                    print("4 passes in sequence ---> a hint is running")
                    if self.hint():
                        pass
                    else:
                        print("No hints are available !")
                t2 = time()
                self.Times[turn] = (t2 - t1)
                turn = not turn
            elif choice == 3: # if user select solve option
                
                for i in range(9):
                    for j in range(9):
                        self.setBoard(i, j, self.getInitialBoard()[i][j])
                self.solve()
                self.print_Board(self.getBoard())
                print("Your score is: 0.0")
                exit()
            elif choice == 4: # if user select exit option
                exit("We will be waiting to see you back again :) ")
            else:
                
                print("Please choose a valid option! ")
            t2 = time()
            self.Times[turn] += (t2-t1)

        P1Score, P2Score = self.ComputeScore(self.Players, self.Times)

        if P1Score > P2Score:
            print("Player 1 Score: "+ str(P1Score)+"\nPlayer 2 Score: "+str(P2Score)+"\nPlayer 1 won !")
        elif P1Score < P2Score:
            print("Player 1 Score: "+ str(P1Score)+"\nPlayer 2 Score: "+str(P2Score)+"\nPlayer 2 won !")
        else:
            print("Player 1 Score: "+ str(P1Score)+"\nPlayer 2 Score: "+str(P2Score)+"\nDraw !")

    # We use this this function to compute score for the player
    def ComputeScore(self, Scores, Times):
        if Scores[0]  > 0 and Scores[1] > 0:
            return [(Scores[0]/self.getSide()*self.getSide())*((Times[0]+Times[1])/Times[0]), (Scores[1]/self.getSide()*self.getSide())*((Times[0]+Times[1])/Times[1])]
        elif Scores[0] <= 0 and Scores[1] > 0:
            return [0, (Scores[1]/self.getSide()*self.getSide())*((Times[0]+Times[1])/Times[1])]
        elif Scores[0]  > 0 and Scores[1] <= 0:
            return [(Scores[0]/self.getSide()*self.getSide())*((Times[0]+Times[1])/Times[0]), 0]
        else:
            return [0,0]