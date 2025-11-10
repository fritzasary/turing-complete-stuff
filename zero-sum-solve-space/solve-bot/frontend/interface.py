import solver
import sys
import random as rnd
import traverse_store as ts


### General main executor to establish the general playing bot
def play_bot():
	#### User interface setup
	available_games = ["Tic-Tac-Three", "Tic-Tac-Four"]
	for i in range(1,len(available_games)+1):
		print("(" + str(i) + ") " + available_games[i-1])
	game = input("\nPick a game to play against Stephanos: " )
	while not (game in [str(i) for i in range(1,len(available_games)+1)]):
		game = input("Pick a game listed to play against Stephanos: ")
	print()
	#### instantiating a specific game setup ####
	match game:
		case "1":
			b = solver.t3board()
			g = solver.tictacthree(b)
			db_path = "/centralized_dbs/tictacthree_positions.db"
		case "2":
			b = solver.t4board()
			g = solver.tictacfour(b)
			db_path = "/centralized_dbs/tictacfour_positions.db"
	

	#### User decide and play 
	turn = input("\nPlay against Stephanos, pick to go first (1) or second (2): ")
	playerMove = ""
	while g.primitiveValue() == solver.gameResult.UNDECIDED:
		print()
		g.printState()
		print()
		if turn == "1": # Player goes first
			playerMove = input("Possible moves: " + str(g.generateMoves()) + ": ")
			while not (playerMove in g.generateMoves()):
				playerMove = input("\nNot a valid move. Possible moves: " + str(g.generateMoves()) + ": ")
			print()
			g = g.doMove(playerMove)
			g.printState()
			if g.primitiveValue() != solver.gameResult.UNDECIDED:
				break

			# Stephanos goes second
			bstMove, bstResult = "", solver.gameResult.WIN
			lstChild = [g.doMove(move) for move in g.generateMoves()]
			lstRecord = {g.doMove(move): ts.traverse("tictactoe", g.doMove(move), db_path) for move in g.generateMoves()}
			lstWin, lstTie, lstLose = [child for child in lstRecord.items() if child[1] == solver.gameResult.WIN], [child for child in lstRecord.items() if child[1] == solver.gameResult.TIE], [child for child in lstRecord.items() if child[1] == solver.gameResult.LOSE]

			if lstLose:
				randChild = rnd.choice(lstLose)[0]
			elif lstTie:
				randChild = rnd.choice(lstTie)[0]
			elif lstWin:
				randChild = rnd.choice(lstWin)[0]
			g = randChild
			if g.primitiveValue() == solver.gameResult.LOSE:
				print()
				print(" I won hehe! ;)")
				print()
				break
		if turn == "2": # Stephanos goes first
			bstMove, stephanosMove, bstResult = "", "", solver.gameResult.LOSE
			lstChild = [g.doMove(move) for move in g.generateMoves()]
			lstRecord = {g.doMove(move): ts.traverse("tictactoe", g.doMove(move), db_path) for move in g.generateMoves()}

			lstWin, lstTie, lstLose = [child for child in lstRecord.items() if child[1] == solver.gameResult.WIN], [child for child in lstRecord.items() if child[1] == solver.gameResult.TIE], [child for child in lstRecord.items() if child[1] == solver.gameResult.LOSE]

			if lstWin:
				randChild = rnd.choice(lstWin)[0]
			elif lstTie:
				randChild = rnd.choice(lstTie)[0]
			elif lstLose:
				randChild = rnd.choice(lstLose)[0]
			g = randChild
			print()
			g.printState()
			print()

			if g.primitiveValue() != solver.gameResult.UNDECIDED:
				break
			playerMove = input("Possible moves: " + str(g.generateMoves()) + ": ") # Player goes second
			while not (playerMove in g.generateMoves()):
				playerMove = input("\nNot a valid move. Possible moves: " + str(g.generateMoves()) + ": ")
			g = g.doMove(playerMove)
	g.printState()
	print()

	#### Match outcome to end display
	match g.primitiveValue():
		case solver.gameResult.TIE: 
			print("It's a tie!\n") # if it get's to this point, it's a tie
		case solver.gameResult.WIN:
			if turn == "1":
				print(" You win... -_-\n")
			else:
				print(" I win! hehe! ;)\n")
		case solver.gameResult.LOSE:
			if turn == "1":
				print(" I win! hehe! ;)\n")
			else:
				print(" You win...! -_-\n")
	play_bot()



def main():
	play_bot()
#	hashdebug()



main()
