from asgn_3_package.pokeman_gym import PokemanGym
from asgn_3_package.pokeman import Pokeman

pokeman_gym = PokemanGym()

pikachu = Pokeman("Pikachu")

# Train until the pokeman reaches the max level
while pikachu.get_level() < Pokeman.MAX_LEVEL:
    pokeman_gym.train_pokeman(pikachu)
    print(pikachu)
