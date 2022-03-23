from Multiplayer import MultyPlayer
from SinglePlayer import SinglePlayer
from game import Sudoku
def getMode(): # get mode from player
    gameMode = int(input("Mode: \n1- Single Player.\n2- Multiplayer.\n"))

    while gameMode != 1 and gameMode != 2:
        gameMode = int(input("Please choose a valid mode"))
    return gameMode

if __name__ == "__main__":
    LoadGame = None
    DifficultyLevel = None
    fileName = None
    while LoadGame != 1 and LoadGame != 2:
        # get type of load the puzzle from a text file or start a random puzzle
        LoadGame = int(input("Please choose to load the puzzle from a text file or start a random puzzle: \n1- Load From a File\n2- Randomly Generate\n"))
    if LoadGame == 1:
        fileName = str(input("Please enter the file full name to load the game from: "))
        gameMode = getMode()
    else:
        while DifficultyLevel != 1 and DifficultyLevel != 2 and DifficultyLevel != 3:
            DifficultyLevel = int(input("Difficulty level is: 1- Easy, 2- Medium, 3- Hard\n"))
        gameMode = getMode()

    if gameMode == 1:
        puzzle = SinglePlayer(GameLoaded=LoadGame, Difficulty=DifficultyLevel, FileName=fileName)

    elif gameMode == 2:
        puzzle = MultyPlayer(GameLoaded=LoadGame, Difficulty=DifficultyLevel, FileName=fileName)
    
    print("Game is ready to play")
    input("Press any key to start the game\n")
    
    puzzle.play()