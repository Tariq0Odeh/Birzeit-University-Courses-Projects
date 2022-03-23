import abc  # abstract methode
import csv   # csv file
from random import sample, randint  # To extract a specific number of numbers within a specific ring
from os import error  # To print errors
class Sudoku:
    _base = 3
    _side = _base*_base 
    _Board = [[0 for i in range(9)] for j in range(9)] 
    # An initial board is made here so that the user is not allowed to modify it while playing
    _InitialBoard = [[0 for i in range(9)] for j in range(9)]
    def __init__(self, GameLoaded, Difficulty=None, FileName=None):
        if GameLoaded == 1:

            self.GenerateFromFile(FileName=FileName)
        elif GameLoaded == 2:
            self.GenerateRandom(Difficulty=Difficulty)
        else:
            error("Error! Something went wrong.")
            
    def getBoard(self):
        return self._Board
    
    def setBoard(self, row, col, value):
        self._Board[row][col] = value

    def getInitialBoard(self):
        return self._InitialBoard
    
    def setInitialBoard(self, row, col, value):
        self._InitialBoard[row][col] = value

    def getBase(self):
        return self._base

    def setBase(self, base):
        self._base = base
        self._side = base*base
    
    def getSide(self):
        return self._side

    # It is used to read the file when the user chooses the option to read from a file.
    def GenerateFromFile(self, FileName):
        try:
            with open(FileName, newline='') as file:
                    csv_reader = csv.reader(file)
                    i = 0
                    for row in csv_reader:
                        self._Board[i] = [int(int(num.replace('', '0'))/10) for num in row]
                        self._InitialBoard[i] = [int(int(num.replace('', '0'))/10) for num in row]
                        while len(self._Board[i]) < 9:
                            self._Board[i].append(0)
                            self._InitialBoard[i].append(0)
                        i = i + 1 
        except:
            print("File entered does not exist")
            exit()
        file.close()

    # It is used to choose random numbers and place them in the puzzle and number them according to the level of difficulty
    def GenerateRandom(self, Difficulty):
        # pattern for a baseline valid solution
        def pattern(r,c): return (self._base*(r%self._base)+r//self._base+c)%self._side
        # randomize rows, columns and numbers (of valid base pattern)
        def shuffle(s): return sample(s,len(s)) 
        rBase = range(self._base) 
        rows  = [ g*self._base + r for g in shuffle(rBase) for r in shuffle(rBase) ] 
        cols  = [ g*self._base + c for g in shuffle(rBase) for c in shuffle(rBase) ]
        nums  = shuffle(range(1,self._base*self._base+1))
        # produce board using randomized baseline pattern
        self._Board = [ [nums[pattern(r,c)] for c in cols] for r in rows ]
        squares = self._side*self._side
        if Difficulty == 1:
            empties = squares * 6//10
        elif Difficulty == 2:
            empties = squares * 75//100
        elif Difficulty == 3:
            empties = squares * 90//100
        else:
            error("Error! Something went wrong.")
        for p in sample(range(squares),empties):
            self._Board[p//self._side][p%self._side] = 0
        
        for row in range(9):
            for col in range(9):
                self._InitialBoard[row][col] = self._Board[row][col]

    # Print bord
    def print_Board(self, Board):
        line0  = self.expandLine("╔═══╤═══╦═══╗")

        line1  = self.expandLine("║ . │ . ║ . ║")

        line2  = self.expandLine("╟───┼───╫───╢")

        line3  = self.expandLine("╠═══╪═══╬═══╣")
        
        line4  = self.expandLine("╚═══╧═══╩═══╝")
        symbol = " 1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        nums   = [ [""]+[symbol[n] for n in row] for row in Board ]
        print(line0)
        for r in range(1,self._side+1):
            
            print("".join(n+s for n,s in zip(nums[r-1],line1.split("."))) )
            print([line2,line3,line4][(r%self._side==0)+(r%self._base==0)])
    def expandLine(self, line):
        return line[0]+line[5:9].join([line[1:5]*(self._base-1)]*self._base)+line[9:13]

    # It is used to solve the puzzle when the user requests
    # We use backtracking algorithm , So that he walks on the board and fills it in with valid values, and if he reaches a point where it is not possible to complete, the values will be zeroed and reset again.
    def solve(self, i=0, j=0):
        i, j = self.findNextCellToFill()
        if i == -1:
            return True
        for e in range(1, 10):
            if self.valid(i, j, e):
                self._Board[i][j] = e
                if self.solve(i, j):
                    return True
                self._Board[i][j] = 0
        return False

    # It is used to give a hint to the player when choosing this option
    def hint(self):
        for row in range(9):
            for col in range(9):
                if self._Board[row][col] == 0:
                    for constant in range(1, 10):
                        if self.valid(row, col, constant):
                            self._Board[row][col] = constant
                            print("["+str(row+1)+"]["+ str(col+1)+ "] = "+str(constant))
                            return True
        return False

    # Checks if the entered values are valid according to the rules of the game
    def valid(self, row, column, val):
        if val < 0 or val > 9:
            return False
        if self._InitialBoard[row][column] != 0:
            return False
        if row < 9 and column < 9 and val == 0:
            return True
        for i in range(9):
            if self._Board[row][i]== val:
                return False
            if self._Board[i][column]== val:
                return False
        i = row//3
        j = column//3
        for row in range(i * 3, i * 3 + 3):
            for column in range (j * 3, j * 3 + 3):
                if self._Board[row][column]== val:
                    return False


        return True

    def Solved(self):
        for row in self._Board:
            for col in row:
                if col == 0:
                    return False
        return True

    @abc.abstractmethod
    def play(self):
        """
        When the game starts, one of the two modes will handle
        this method to play within its' laws
        """
        pass

    @abc.abstractclassmethod
    def ComputeScore(self):
        pass

    def findNextCellToFill(self):
        for x in range(9):
            for y in range(9):
                if self._Board[x][y] == 0:
                    return x, y
        return -1, -1