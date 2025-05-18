from asgn_3_package.pokeman_gym import PokemanGym
from asgn_3_package.pokeman import Pokeman, SoftEngPokeman
from asgn_3_package.softeng_pokeman_trainer import PokemonSelfChanger


pikachu = Pokeman("Pikachu")
softeng_pokeman = SoftEngPokeman("Pikachu_softeng")

'''three observers'''
pokeman_gym = PokemanGym()
pkm_self_changer = PokemonSelfChanger(pikachu)        # at first Pokemon, at last epoch change to softeng_pokeman

pikachu.add_training_observer(pkm_self_changer)
pikachu.add_training_observer(pokeman_gym)


'''train: only update softeng pokemon at the last level'''
while softeng_pokeman.get_cur_level() < Pokeman.MAX_LEVEL:

    pkm_self_changer.set_new_self(softeng_pokeman)
    pokeman_gym.train_pokeman(pikachu)
    pikachu.set_myself(pikachu)
    pkm_self_changer.set_new_self(pikachu)
    pokeman_gym.train_pokeman(pikachu)

    print(pikachu)
    print(softeng_pokeman)