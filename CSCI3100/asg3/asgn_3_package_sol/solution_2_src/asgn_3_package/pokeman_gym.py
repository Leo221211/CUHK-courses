from threading import Thread

from asgn_3_package.pokeman import Pokeman
from asgn_3_package.training import (
    TrainingStatusObserver,
    Trainable,
    TrainingData,
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

        print(f"Training {pokeman.get_name()} in the gym")

        if pokeman.get_training_property("level") == Pokeman.MAX_LEVEL:
            print("Pokeman is at max level!")
            return

        # Training time is exponential to the level of the pokeman
        training_time = 2 ** int(pokeman.get_training_property("level"))

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
        print(f"{obj.get_training_property("name")} has finished training!")

        new_level = int(obj.get_training_property("level")) + 1
        training_data = TrainingData()
        training_data.set_attribute_value("level", new_level)
        training_data.set_attribute_value("hp", new_level * 10)
        training_data.set_attribute_value("attack", new_level * 5)
        training_data.set_attribute_value("defense", new_level * 5)
        training_data.set_attribute_value("speed", new_level * 5)
        obj.update_stats(training_data)

        self._training_done = True
