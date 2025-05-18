from threading import Thread

from asgn_3_package.pokeman import Pokeman
from asgn_3_package.training import (
    TrainingStatusObserver,
    Trainable,
)

class PokemanGym(TrainingStatusObserver):
    """
    Represents a Pokeman Gym in the Pokeman world

    Pokemans can get trained in this gym to increase their stats

    Since PokemanGym implements PokemanTrainingStatusObserver, it can observe the training status of a pokeman
    """

    def __init__(self):
        # A thread to be used to train the pokeman, to make the training process non-blocking
        self._training_thread: Thread = None
        self._training_done = False

    def check_pokeman_class_hierarchy(self, pokeman: Pokeman) -> bool:
        if (not isinstance(pokeman, (Pokeman))) and (Pokeman in type(pokeman).mro()):
            print(f"Input has type {type(pokeman)}")
            print(f"  Parent classes: {type(pokeman).mro()}")
            print(f"  Not allowed: The input has inherited from Pokeman: {Pokeman}")
            return False
        return True

    def train_pokeman(self, pokeman: Pokeman):
        """
        Trains the pokeman to increase its stats
        """
        self._training_done = False

        if not self.check_pokeman_class_hierarchy(pokeman):
            print("Cannot train the pokeman! It cannot be inherited from Pokeman")
            return

        pokeman.add_training_observer(self)

        print(f"Training {pokeman.get_attribute('name')} in the gym")

        if pokeman.get_cur_level() == Pokeman.MAX_LEVEL:
            print("Pokeman is at max level!")
            return

        # Training time is exponential to the level of the pokeman
        training_time = 2 ** pokeman.get_cur_level()

        # Start a new thread to train the pokeman
        # The thread will be joined and deleted after the training is complete
        self._training_thread = Thread(target=pokeman.practice, args=(training_time,))
        self._training_thread.start()
        while not self._training_done:
            print("    training")
            # Help the pokeman determine its type
            pokeman.determine_type()
            self._training_thread.join(1)
        self._training_thread.join()
        del self._training_thread

    def finished_training(self, obj: Trainable):
        print(f"{obj.get_attribute('name')} has finished training!")

        new_level = obj.get_cur_level() + 1
        stats_dict = {
            'level': new_level,
            'hp': new_level * 10,
            'attack': new_level * 5,
            'defence': new_level * 5,
            'speed': new_level * 5
        }
        # obj.update_stats(
        #     new_level,
        #     new_level * 10,
        #     new_level * 5,
        #     new_level * 5,
        #     new_level * 5,
        # )
        obj.update_stats(stats_dict)

        self._training_done = True
