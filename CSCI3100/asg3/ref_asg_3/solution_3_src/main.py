from asgn_3_package.pokeman_gym import PokemanGym
from asgn_3_package.pokeman import SoftEngPokeman
from asgn_3_package.softeng_pokeman_trainer import SoftEngPokeman

# pokeman_gym = PokemanGym()

# pikachu = Pokeman("Pikachu")

# # Train until the pokeman reaches the max level
# while pikachu.get_level() < Pokeman.MAX_LEVEL:
#     pokeman_gym.train_pokeman(pikachu)
#     print(pikachu)


pokeman_gym = PokemanGym()
softeng_pokeman = SoftEngPokeman("Pikachu")
while softeng_pokeman.get_cur_level() < SoftEngPokeman.MAX_LEVEL:
    pokeman_gym.train_pokeman(softeng_pokeman)
    print(softeng_pokeman)
