from abc import ABC, abstractmethod


class TrainingData:
    def __init__(self):
        self._attributes_to_update = {}  # A dictionary of attributes to update

    def set_attribute_value(self, attribute_name: str, value):
        """
        attribute_name: The name of the attribute to set
        value: The value to set, can be of any type
        """
        self._attributes_to_update[attribute_name] = value

    def get_attribute_value(self, attribute_name: str) -> object:
        """
        attribute_name: The name of the attribute to get

        returns the value that can be of any type
        """
        return self._attributes_to_update[attribute_name]


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
    def update_stats(self, training_data: TrainingData):
        """
        Update the stats after training
        """

    @abstractmethod
    def get_training_property(self, property_name: str) -> object:
        """
        Get a property of the object

        The property can be a string or an integer
        """
