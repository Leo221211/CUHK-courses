from threading import Thread

from asgn_3_package.pokeman import Pokeman
from asgn_3_package.training import (
    Trainable,
    TrainingStatusObserver,
)


class PokemonSelfChanger(TrainingStatusObserver):
    """An observer that is used to change the _myself of a Pokeman to something else"""

    def __init__(self, new_self: None):
        self._new_self = new_self

    def set_new_self(self, new_self):
        self._new_self = new_self

    def finished_training(self, obj: Trainable):
        obj._myself = self._new_self
        print(f"Changed the _myself of {obj.get_name()} to {self._new_self}")