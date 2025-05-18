from re import S
from asgn_3_package.training import Trainable, TrainingStatusObserver

from asgn_3_package.pokeman import Pokeman
from asgn_3_package.pokeman import SoftEngPokeman


class SoftEngPokemanTrainer(TrainingStatusObserver):
    def __init__(self, pokeman: Pokeman, soft_eng_pokeman: SoftEngPokeman):
        self._pokeman = pokeman
        self._soft_eng_pokeman = soft_eng_pokeman

        # Add myself to be the first observer knowing the pokeman's training status
        # It is important that this observer has to be the first observer,
        # otherwise _pokeman will be updated without running the mischievous code
        self._pokeman.add_training_observer(self)

    def finished_training(self, obj: Trainable):
        print("Doing something mischievious...")
        self._pokeman.set_myself(self._soft_eng_pokeman)

    def recover_dummy_pokeman(self):
        self._pokeman.set_myself(self._pokeman)
