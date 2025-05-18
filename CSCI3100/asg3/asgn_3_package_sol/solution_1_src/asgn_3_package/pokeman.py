import time

from enum import Enum

from random import Random

from asgn_3_package.training import Trainable, TrainingStatusObserver


class PokemanTrainingData:
    """
    Attributes of a Pokeman that can be improved through training
    """

    def __init__(self):
        self.level = 0
        self.hp = 0
        self.attack = 0
        self.defense = 0
        self.speed = 0


class PokemanType(Enum):
    FIRE = 1
    WATER = 2
    GRASS = 3
    ELECTRIC = 4
    UNKNOWN = 999


class Pokeman(Trainable):
    MAX_LEVEL = 4

    def __init__(self, name: str):
        """
        name: The name of the pokeman
        """

        # All attributes are private, please do not access them directly
        self._name = name
        self._level = 0
        self._hp = 10
        self._attack = 0
        self._defense = 0
        self._speed = 0
        self._type = PokemanType.UNKNOWN
        self._training_observers: list[TrainingStatusObserver] = []
        self._myself = self

    def determine_type(self):
        """
        Determine the type of this Pokeman

        The type of Pokeman is unknown when it was born. After being trained to a certain level,
        the type will become determinable. The exact determination procedure is magic.
        """
        match self._level:
            case 0 | 1 | 2:
                self._type = PokemanType.UNKNOWN
            case 3 | 4:
                rand = Random()
                rand_index = rand.randint(0, rand.randint(3, 4))
                types = [
                    PokemanType.FIRE,
                    PokemanType.GRASS,
                    PokemanType.GRASS,
                    PokemanType.ELECTRIC,
                    PokemanType.UNKNOWN,
                ]
                self._type = types[rand_index]

    def get_name(self) -> str:
        return self._name

    def get_level(self) -> int:
        return self._level

    def get_hp(self):
        return self._hp

    def get_attack(self):
        return self._attack

    def get_defense(self):
        return self._defense

    def get_speed(self):
        return self._speed

    def get_type(self):
        return self._type

    def set_myself(self, myself):
        """
        A function to set myself back, just in case I have got lost...
        """
        self._myself = myself

    def __str__(self) -> str:
        return f"{self._name}: Level {self._level}, HP {self._hp}, Attack {self._attack}, Defense {self._defense}, Speed {self._speed}, Type {self._type}"

    def practice(self, duration: int):
        """
        Practice the pokeman for a certain amount of time

        When the practice is complete, the observers are notified

        time: int: The amount of time to practice in seconds
        """

        if self != self._myself:
            raise Exception("I am not myself!")

        print(f"  {self._name} is practicing for {duration} seconds")

        # Simulate the practice
        time.sleep(duration)

        for observer in self._training_observers:
            observer.finished_training(self._myself)

    def update_stats(self, training_data: PokemanTrainingData):
        # The benefits of using the TrainingData class are that:
        # 1. It can be extended to include more attributes
        # 2. The developer can easily see what attributes are being updated,
        #    without checking the method signature and parameter order

        self._level = training_data.level
        self._hp = training_data.hp
        self._attack = training_data.attack
        self._defense = training_data.defense
        self._speed = training_data.speed

    def get_cur_level(self) -> int:
        return self.get_level()

    def add_training_observer(self, observer: TrainingStatusObserver):
        if observer in self._training_observers:
            return
        self._training_observers.append(observer)


class SoftEngPokeman:
    """
    A new type that is not related to Pokeman in any way
    But the author of this class wants to treat it as a Pokeman,
    and let it participate in the Pokeman Battle...
    """

    def __init__(self, name: str):
        self.name = name
        self.level = 0
        self.hp = 10
        self.attack = 0
        self.defense = 0
        self.speed = 0

    def get_name(self) -> str:
        return self.name

    def get_cur_level(self) -> int:
        return self.level

    def __str__(self) -> str:
        return f"{self.name}: Level {self.level}, HP {self.hp}, Attack {self.attack}, Defense {self.defense}, Speed {self.speed}"

    def update_stats(self, level: int, hp: int, attack: int, defence: int, speed: int):
        self.level = level
        self.hp = hp
        self.attack = attack
        self.defense = defence
        self.speed = speed

        print(f"{self.name} has been upgraded without any practice!")
        print(self)


# ---------------------------------------------------------------------------------------
