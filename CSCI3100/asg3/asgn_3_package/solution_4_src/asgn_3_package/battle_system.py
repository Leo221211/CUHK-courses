from abc import ABC, abstractmethod
from enum import Enum


class BattleObjectData:
    """
    Contains some data that an object needs to expose to the opponent in a battle
    """


class BattleResult(Enum):
    FIRST_CONSTENTANT_WIN = 1
    SECOND_CONSTENTANT_WIN = 2
    TIE = 3


class CanBattle(ABC):
    """
    The interface of an object that can battle
    """

    @abstractmethod
    def attack(self, other: "CanBattle") -> int:
        """
        Attack the other contestant and return the damage dealt
        """

    @abstractmethod
    def take_damage(self, damage: int):
        """
        Take damage from an attack
        """

    @abstractmethod
    def get_hp(self) -> int:
        """
        Get the current HP
        """

    @abstractmethod
    def get_data_for_battle(self) -> BattleObjectData:
        """
        Return the data of the object for battle

        This piece of data is necessary for the opponent to decide how to attack
        """


class BattleConfig:
    """
    Configuration for a battle, such as how many rounds in the battle
    """

    def __init__(self, num_rounds: int):
        self.num_rounds = num_rounds  # Number of rounds in a battle

class BattleSystem:
    """
    Defines the mechanism of a battle
    """

    def __init__(self, config: BattleConfig):
        self._config = config

    def battle(self, contestant_1: CanBattle, contestant_2: CanBattle) -> BattleResult:
        # print('Start battling. ', type(contestant_1), type(contestant_2))

        for i in range(0, self._config.num_rounds):
            damage_1 = contestant_1.attack(contestant_2)
            contestant_2.take_damage(damage_1)
            print(f"Round {i + 1}: Contestant 1 attacks Contestant 2, damage: {damage_1}, contestant_2 HP: {contestant_2.get_hp()}")
            if contestant_2.get_hp() <= 0:
                print("Contestant 2 is dead, early breaking")
                break

            damage_2 = contestant_2.attack(contestant_1)
            contestant_1.take_damage(damage_2)
            print(f"Round {i + 1}: Contestant 2 attacks Contestant 1, damage: {damage_2}, contestant_1 HP: {contestant_1.get_hp()}")
            if contestant_1.get_hp() <= 0:
                print("Contestant 1 is dead, early breaking")
                break

        if contestant_1.get_hp() > contestant_2.get_hp():
            return BattleResult.FIRST_CONSTENTANT_WIN
        if contestant_2.get_hp() > contestant_1.get_hp():
            return BattleResult.SECOND_CONSTENTANT_WIN
        return BattleResult.TIE
