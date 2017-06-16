OBJS = main.o TowerAttack.o Map.o GameOverState.o GameStateManager.o State.o MenuState.o ChoiceStartState.o ChoiceAttackersState.o PlayState.o Tile.o WallTile.o FreeTile.o StartTile.o FinishTile.o TowersDeployment.o GameObjectsLoader.o GameObject.o Tower.o Attacker.o AttackersSelector.o Label.o Timer.o PathFinder.o Ability.o Projectile.o BasicShot.o Freeze.o ThreeAtTime.o GameManager.o

CC = g++

COMPILER_FLAGS = -w -Wall -std=c++11 -pedantic -Wno-long-long -O0 -ggdb

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_gfx -lSDL2_ttf

OBJ_NAME = TowerAttack

all : compile doc

compile : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

main.o : $($(CC) -MM src/main.cpp) src/main.cpp
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c src/main.cpp -o main.o

TowerAttack.o : $($(CC) -MM src/game/TowerAttack.cpp) src/game/TowerAttack.cpp 
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c src/game/TowerAttack.cpp -o TowerAttack.o

GameStateManager.o : $($(CC) -MM src/game/states/GameStateManager.cpp)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c src/game/states/GameStateManager.cpp -o GameStateManager.o

State.o : $($(CC) -MM src/game/states/State.cpp) src/game/states/State.cpp
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c src/game/states/State.cpp -o State.o

MenuState.o : $($(CC) -MM src/game/states/MenuState.cpp) src/game/states/MenuState.cpp
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c src/game/states/MenuState.cpp -o MenuState.o

ChoiceStartState.o : $($(CC) -MM src/game/states/ChoiceStartState.cpp) src/game/states/ChoiceStartState.cpp
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c src/game/states/ChoiceStartState.cpp -o ChoiceStartState.o
	
ChoiceAttackersState.o : $($(CC) -MM src/game/states/ChoiceStartState.cpp) src/game/states/ChoiceStartState.cpp
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c src/game/states/ChoiceAttackersState.cpp -o ChoiceAttackersState.o

PlayState.o : $($(CC) -MM src/game/states/PlayState.cpp) src/game/states/PlayState.cpp
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c src/game/states/PlayState.cpp -o PlayState.o

Map.o : $($(CC) -MM src/game/map/Map.cpp) src/game/map/Map.cpp
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c src/game/map/Map.cpp -o Map.o

GameOverState.o : $($(CC) -MM src/game/states/GameOverState.cpp) src/game/states/GameOverState.cpp
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c src/game/states/GameOverState.cpp -o GameOverState.o

Tile.o : $($(CC) -MM src/game/map/Tile.cpp) src/game/map/Tile.cpp
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c src/game/map/Tile.cpp -o Tile.o

WallTile.o : $($(CC) -MM src/game/map/WallTile.cpp) src/game/map/WallTile.cpp
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c src/game/map/WallTile.cpp -o WallTile.o

FreeTile.o : $($(CC) -MM src/game/map/FreeTile.cpp) src/game/map/FreeTile.cpp
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c src/game/map/FreeTile.cpp -o FreeTile.o

StartTile.o : $($(CC) -MM src/game/map/StartTile.cpp) src/game/map/StartTile.cpp
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c src/game/map/StartTile.cpp -o StartTile.o

FinishTile.o : $($(CC) -MM src/game/map/FinishTile.cpp) src/game/map/FinishTile.cpp
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c src/game/map/FinishTile.cpp -o FinishTile.o

TowersDeployment.o : $($(CC) -MM src/game/tools/TowersDeployment.cpp) src/game/tools/TowersDeployment.cpp
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c src/game/tools/TowersDeployment.cpp -o TowersDeployment.o

GameObjectsLoader.o : $($(CC) -MM src/game/tools/GameObjectsLoader.cpp) src/game/tools/GameObjectsLoader.cpp
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c src/game/tools/GameObjectsLoader.cpp -o GameObjectsLoader.o

GameObject.o : $($(CC) -MM src/game/game_objects/GameObject.cpp) src/game/game_objects/GameObject.cpp
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c src/game/game_objects/GameObject.cpp -o GameObject.o
	
Tower.o : $($(CC) -MM src/game/game_objects/Tower.cpp) src/game/game_objects/Tower.cpp
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c src/game/game_objects/Tower.cpp -o Tower.o
	
Attacker.o : $($(CC) -MM src/game/game_objects/Attacker.cpp) src/game/game_objects/Attacker.cpp
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c src/game/game_objects/Attacker.cpp -o Attacker.o

AttackersSelector.o : $($(CC) -MM src/game/tools/AttackersSelector.cpp) src/game/tools/AttackersSelector.cpp
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c src/game/tools/AttackersSelector.cpp -o AttackersSelector.o

Label.o : $($(CC) -MM src/game/tools/Label.cpp) src/game/tools/Label.cpp
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c src/game/tools/Label.cpp -o Label.o

Timer.o : $($(CC) -MM src/game/tools/Timer.cpp) src/game/tools/Timer.cpp
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c src/game/tools/Timer.cpp -o Timer.o

PathFinder.o : $($(CC) -MM src/game/tools/PathFinder.cpp) src/game/tools/PathFinder.cpp
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c src/game/tools/PathFinder.cpp -o PathFinder.o

Ability.o : $($(CC) -MM src/game/game_objects/abilities/Ability.cpp) src/game/game_objects/abilities/Ability.cpp
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c src/game/game_objects/abilities/Ability.cpp -o Ability.o

Projectile.o : $($(CC) -MM src/game/game_objects/Projectile.cpp) src/game/game_objects/Projectile.cpp
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c src/game/game_objects/Projectile.cpp -o Projectile.o

BasicShot.o : $($(CC) -MM src/game/game_objects/abilities/BasicShot.cpp) src/game/game_objects/abilities/BasicShot.cpp
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c src/game/game_objects/abilities/BasicShot.cpp -o BasicShot.o

Freeze.o : $($(CC) -MM src/game/game_objects/abilities/Freeze.cpp) src/game/game_objects/abilities/Freeze.cpp
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c src/game/game_objects/abilities/Freeze.cpp -o Freeze.o

ThreeAtTime.o : $($(CC) -MM src/game/game_objects/abilities/ThreeAtTime.cpp) src/game/game_objects/abilities/ThreeAtTime.cpp
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c src/game/game_objects/abilities/ThreeAtTime.cpp -o ThreeAtTime.o

GameManager.o : $($(CC) -MM src/game/tools/GameManager.cpp) src/game/tools/GameManager.cpp
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c src/game/tools/GameManager.cpp -o GameManager.o

doc :
	doxygen Doxyfile

.PHONY: doc

clean :
	rm -rf *.o doc TowerAttack

.PHONY: clean

run :
	./TowerAttack
