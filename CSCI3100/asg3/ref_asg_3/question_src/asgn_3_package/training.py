from abc import ABC, abstractmethod


class TrainingStatusObserver(ABC):
    """
    An interface of expected functions for observing the training status of an object
    """

    @abstractmethod
    def finished_training(self, obj: "Trainable"):
        """
        When the obj is trained, this method is called
        """


class Trainable(ABC):
    """
    An interface of expected functions that an object that can be trained should provide
    """

    @abstractmethod
    def add_training_observer(self, observer: TrainingStatusObserver):
        """
        Adds an observer to the object
        """

    def practice(self, duration: int):
        """
        Practise for a certain amount of time

        When the practice is complete, the observers are notified

        time: int: The amount of time to practice in seconds
        """

    @abstractmethod
    def update_stats(self, level: int, hp: int, attack: int, defence: int, speed: int):
        """
        Update the stats after training
        """

    @abstractmethod
    def get_cur_level(self) -> int:
        """
        Get the current level of the object
        """

    @abstractmethod
    def get_name(self) -> str:
        """
        Get the object's name
        """
