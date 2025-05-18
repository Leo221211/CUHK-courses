from abc import ABC, abstractmethod
from enum import Enum


class BattleObjectData:
    """
    Contains some data that an object needs to expose to the opponent in a battle
    """

    # anything will do
    def __init__(self, hp: int, attack: int, defence: int, speed: int):
        self.hp = hp
        self.attack = attack
        self.defence = defence
        self.speed = speed


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
        for i in range(0, self._config.num_rounds):
            damage_1 = contestant_1.attack(contestant_2)
            damage_2 = contestant_2.attack(contestant_1)

            contestant_2.take_damage(damage_1)
            contestant_1.take_damage(damage_2)

        if contestant_1.get_hp() > contestant_2.get_hp():
            return BattleResult.FIRST_CONSTENTANT_WIN
        if contestant_2.get_hp() > contestant_1.get_hp():
            return BattleResult.SECOND_CONSTENTANT_WIN
        return BattleResult.TIE
