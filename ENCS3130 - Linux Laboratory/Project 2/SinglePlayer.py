from game import Sudoku
import time
class SinglePlayer(Sudoku):
    Score = 0
    def __init__(self, GameLoaded, Difficulty, FileName):
        super().__init__(GameLoaded, Difficulty=Difficulty, FileName=FileName)

    # This function is used when choosing to play the single-player method

    def play(self):
        t1 = time.time()  # The time the player started playing
        while not self.Solved():
            self.print_Board(self.getBoard())
            choice = 0
            try:
                choice = int(input("1- Fill 2- Hint 3- Solve 4- Exit the game\n"))
            except:
                pass
            if choice == 1:  # if user select fill option
                data = tuple(input("You must enter the data like: row column number\n").split(' '))   

                previous = self.getBoard()[int(data[0])-1][int(data[1])-1]

                if self.valid(int(data[0])-1, int(data[1])-1, int(data[2])):
                    self.setBoard(int(data[0])-1, int(data[1])-1,  int(data[2]))
                    
                    if int(data[2] != 0) and previous == 0:
                        self.Score+=1
                    
                else:
                    
                    print("Invalid! Your score will be reduced by 1 !")
                    self.Score-=1
            elif choice == 2: # if user select hint option
                
                if self.hint():
                    print("Your score will be reduced by 2 !")
                    self.Score -= 2

                else:
                    print("No hints are available !")
                    
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
        t2 = time.time() # The time the player finished playing
        TimeConsumed = t2 - t1
        print("Your Score is: "+str(self.ComputeScore(TimeConsumed)))
        exit("Game Over !")
    # We use this this function to compute score for the player
    def ComputeScore(self, TimeConsumed):
        if self.Score <= 0:
            return 0
        else:
            return 3600/TimeConsumed * self.Score/(self.getSide()*self.getSide())
        


