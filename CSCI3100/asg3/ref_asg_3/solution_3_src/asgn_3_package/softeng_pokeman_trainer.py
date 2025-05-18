import time

from enum import Enum

from random import Random

from asgn_3_package.pokeman import SoftEngPokeman, PokemanType
from asgn_3_package.training import (
    TrainingStatusObserver,
)

class SoftEngPokeman(SoftEngPokeman):
    MAX_LEVEL = 4

    def __init__(self, name: str):
        super().__init__(name)
        self._type = PokemanType.UNKNOWN
        self._training_observers: list[TrainingStatusObserver] = []
        self._myself = self

    def add_training_observer(self, observer: TrainingStatusObserver):
        if observer in self._training_observers:
            return
        self._training_observers.append(observer)

    def practice(self, duration: int):
        """
        Practice the pokeman for a certain amount of time

        When the practice is complete, the observers are notified

        time: int: The amount of time to practice in seconds
        """

        if self != self._myself:
            raise Exception("I am not myself!")

        print(f"  {self.name} is practicing for {duration} seconds")

        # Simulate the practice
        time.sleep(duration)

        for observer in self._training_observers:
            observer.finished_training(self._myself)

    def determine_type(self):
        """
        Determine the type of this Pokeman

        The type of Pokeman is unknown when it was born. After being trained to a certain level,
        the type will become determinable. The exact determination procedure is magic.
        """
        match self.level:
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
                self.type = types[rand_index]
