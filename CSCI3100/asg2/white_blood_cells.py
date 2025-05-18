from abc import ABC, abstractmethod
from typing import List, Dict

class Antigen(ABC):
    pass

class Enemy(ABC):
    def __init__(self, has_been_seen_before: bool, antigens: List[Antigen]):
        self.has_been_seen_before: bool = has_been_seen_before
        self.antigens: List[Antigen] = antigens


class Antibody:
    def __init__(self):
        self.__enemy: Enemy

    def set_enemy(self, enemy: Enemy):
        self.__enemy = enemy
        pass

    def can_kill_enemy(self, enemy: Enemy) -> bool:
        pass

    def kill_enemy(self, enemy: Enemy) -> bool:
        pass

class WhiteBloodCell(ABC):
    def __init__(self):
        pass

    @abstractmethod
    def is_enemy(self, antigens: List[Antigen]) -> bool:
        pass

    @abstractmethod
    def kill(self, enemy: Enemy) -> bool:
        pass

class Neutrophils(WhiteBloodCell):
    def __init__(self):
        super().__init__()

    def is_enemy(self, antigens: List[Antigen]) -> bool:
        pass

    def kill(self, enemy: Enemy) -> bool:
        pass

class Lymphocytes(WhiteBloodCell):
    def __init__(self):
        super().__init__()

    @abstractmethod
    def is_enemy(self, antigens: List[Antigen]) -> bool:
        pass

    @abstractmethod
    def kill(self, enemy: Enemy) -> bool:
        pass

class NKCell(Lymphocytes):
    def __init__(self):
        super().__init__()

    def is_enemy(self, antigens: List[Antigen]) -> bool:
        pass

    def kill(self, enemy: Enemy) -> bool:
        pass

class TCell(Lymphocytes):
    def __init__(self):
        super().__init__()
        self.is_activated: bool = False

    def is_enemy(self, antigens: List[Antigen]) -> bool:
        pass

    def kill(self, enemy: Enemy) -> bool:
        pass

class HelperTCell(TCell):
    def __init__(self):
        super().__init__()
        self.__enemy_to_characteristics: Dict[Enemy, List[float]]

    def get_enemy_characteristics(self, enemy: Enemy) -> List[float]:
        pass

class BCell(Lymphocytes):
    def __init__(self):
        super().__init__()

    def is_enemy(self, antigens: List[Antigen]) -> bool:
        pass

    def kill(self, enemy: Enemy) -> bool:
        pass

    def make_antibodies(self, enemy: Enemy) -> Antibody:
        pass

    def ask_helper_t_cell_make_antibodies(self, t_cell: HelperTCell):
        pass

##