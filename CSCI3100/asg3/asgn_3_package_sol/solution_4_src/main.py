from asgn_3_package.battle_system import BattleConfig, BattleSystem
from asgn_3_package.pokeman_gym import PokemanGym
from asgn_3_package.pokeman import Pokeman, SoftEngPokeman

from asgn_3_package.softeng_pokeman_trainer import SoftEngPokemanTrainer

pokeman_gym = PokemanGym()

chukapi = Pokeman("ChuKaPi")

# Train until ChuKaPi reaches the max level
while chukapi.get_level() < Pokeman.MAX_LEVEL:
    pokeman_gym.train_pokeman(chukapi)
    print(chukapi)

# Train until the soft_eng_pokeman reaches the max level
dummy_pikachu = Pokeman("Dummy Pikachu")
kei = SoftEngPokeman("Kei")
softeng_trainer = SoftEngPokemanTrainer(dummy_pikachu, kei)
while kei.get_cur_level() < Pokeman.MAX_LEVEL:
    pokeman_gym.train_pokeman(dummy_pikachu)
    softeng_trainer.recover_dummy_pokeman()
    print(dummy_pikachu)

# Battle!
battle_system = BattleSystem(BattleConfig(3))
print(f"!!! {chukapi} VS. {kei} !!!")
battle_result = battle_system.battle(chukapi, kei)
print(f"Battle result: {battle_result}")
