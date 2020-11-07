import numpy as np
from typing import Iterable, List


class PetriNet:

    def __init__(self, n_transition: int, n_position: int, markup: List) -> None:
        assert(n_transition > 0)
        assert(n_position == len(markup))

        self.I = np.zeros((n_position, n_transition), dtype=np.int)
        self.O = np.zeros((n_transition, n_position), dtype=np.int)
        self.markup = np.array(markup)

    def set_input(self, trans_idx: int, pos_idx: int, edge_count: int) -> None:
        assert(pos_idx < self.I.shape[0])
        assert(pos_idx >= 0)
        assert(trans_idx < self.I.shape[1])
        assert(trans_idx >= 0)
        assert(edge_count >= 0)

        self.I[pos_idx, trans_idx] = edge_count

    def set_output(self, trans_idx: int, pos_idx: int, edge_count: int) -> None:
        assert(pos_idx < self.O.shape[1])
        assert(pos_idx >= 0)
        assert(trans_idx < self.O.shape[0])
        assert(trans_idx >= 0)
        assert(edge_count >= 0)

        self.O[trans_idx, pos_idx] = edge_count

    def _is_possible(self, trans_idx: int) -> bool:
        return np.all((self.markup - self.I[:, trans_idx]) >= 0)

    def __iter__(self):
        return self

    def __next__(self) -> Iterable:
        trans_idx = np.arange(self.O.shape[0])
        np.random.shuffle(trans_idx)
        markup_diff = np.zeros_like(self.markup)

        for i in trans_idx:
            if(self._is_possible(i)):
                self.markup -= self.I[:, i]
                markup_diff += self.O[i, :]

        self.markup += markup_diff
        return self.markup
