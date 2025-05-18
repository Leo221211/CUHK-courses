from asgn_3_package.pokeman_gym import PokemanGym
from asgn_3_package.pokeman import Pokeman
from asgn_3_package.softeng_pokeman_trainer import SoftEngPokeman
from asgn_3_package.battle_system import BattleSystem, BattleConfig

# pokeman_gym = PokemanGym()

# pikachu = Pokeman("Pikachu")

# # Train until the pokeman reaches the max level
# while pikachu.get_level() < Pokeman.MAX_LEVEL:
#     pokeman_gym.train_pokeman(pikachu)
#     print(pikachu)


print('Creating ChuKaPi')
ckp = Pokeman("ChuKaPi")
gym_ckp = PokemanGym()


# Train both to max level
print('Traininig normal pokeman')
while ckp.get_level() < Pokeman.MAX_LEVEL:
    gym_ckp.train_pokeman(ckp)
    print(ckp)
print('normal pokeman reached max level\n')

# print('Creating ChuKaPi2')
# ckp2 = Pokeman("ChuKaPi2")
# gym_ckp2 = PokemanGym()


# # Train both to max level
# print('Traininig normal pokeman 2')
# while ckp2.get_level() < Pokeman.MAX_LEVEL:
#     gym_ckp2.train_pokeman(ckp2)
#     print(ckp2)
#     break

print('Creating Kei')
kei = SoftEngPokeman("Kei")
gym_kei = PokemanGym()

print('Training Kei')
while kei.get_cur_level() < SoftEngPokeman.MAX_LEVEL:
    gym_kei.train_pokeman(kei)
    print(kei)
print('softeng pokeman reached max level\n')


# Battle
print('Start battling')
battle = BattleSystem(BattleConfig(num_rounds=1))
# print(type(ckp), type(kei))
result = battle.battle(ckp, kei)
print(f"Result: {result}")