from PetriNet import PetriNet
import numpy as np


def variant1() -> PetriNet:
    init_markup = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0]
    net = PetriNet(10, 15, init_markup)

    for i in range(5):
        net.set_input(i, i, 1)
        net.set_input(i, i + 5, 1)
        if i != 0:
            net.set_input(i, i + 4, 1)
        else:
            net.set_input(0, 9, 1)
        net.set_output(i, i+10, 1)

        net.set_input(i+5, i+10, 1)
        net.set_output(i+5, i+5, 1)
        net.set_output(i+5, i, 1)
        if i != 0:
            net.set_output(i+5, i+4, 1)
        else:
            net.set_output(5, 9, 1)

    return net


def variant2() -> PetriNet:
    init_markup = [1, 1, 1, 1, 1,  # walking position
                   1, 1, 1, 1, 1,  # forks position
                   0, 0, 0, 0, 0,  # philosoph takes left fork
                   0, 0, 0, 0, 0]  # eating
    net = PetriNet(15, 20, init_markup)

    for i in range(5):
        net.set_input(i, i, 1)
        net.set_input(i, i + 5, 1)
        net.set_output(i, i+10, 1)

        net.set_input(i+5, i+10, 1)
        if i != 4:
            net.set_input(i+5, i+11, 1)
        else:
            net.set_input(9, 10, 1)
        net.set_output(i+5, i+15, 1)
        if i != 4:
            net.set_output(i+5, i+1, 1)
        else:
            net.set_output(9, 0, 1)

        net.set_input(i+10, i+15, 1)
        net.set_output(i+10, i, 1)
        net.set_output(i+10, i+5, 1)
        if i != 4:
            net.set_output(i+10, i+6, 1)
        else:
            net.set_output(14, 5, 1)

    return net


def variant3() -> PetriNet:
    init_markup = [1, 1, 1, 1, 1,  # walking position
                   1, 1, 1, 1, 1,  # forks position
                   0, 0, 0, 0, 0,  # philosoph takes left fork
                   0, 0, 0, 0, 0,  # philosoph take right fork
                   0, 0, 0, 0, 0,  # sitting
                   0, 0, 0, 0, 0]  # eating
    net = PetriNet(30, 30, init_markup)

    for i in range(5):
        # can take left fork?
        net.set_input(i, i, 1)
        net.set_input(i, i + 5, 1)
        net.set_output(i, i+10, 1)

        # will take away from the right neighbor?
        net.set_input(i+5, i+10, 1)
        if i != 4:
            net.set_input(i+5, i+11, 1)
        else:
            net.set_input(9, 10, 1)
        net.set_output(i+5, i+15, 1)
        if i != 4:
            net.set_output(i+5, i+1, 1)
        else:
            net.set_output(9, 0, 1)

        # Select sitting
        net.set_input(i+10, i+10, 1)
        net.set_output(i+10, i+20, 1)
        if i != 0:
            net.set_input(i+10, i-1, 1)
            net.set_output(i+10, i-1, 1)
        else:
            net.set_input(10, 4, 1)
            net.set_output(10, 4, 1)

        # Start eating
        net.set_input(i+15, i+15, 1)
        net.set_output(i+15, i+25, 1)

        # End of sitting
        net.set_input(i+20, i+20, 1)
        net.set_output(i+20, i, 1)
        net.set_output(i+20, i+5, 1)

        # End of eating
        net.set_input(i+25, i+25, 1)
        net.set_output(i+25, i, 1)
        net.set_output(i+25, i+5, 1)
        if i != 4:
            net.set_output(i+25, i+6, 1)
        else:
            net.set_output(29, 5, 1)

    return net


def variant4() -> PetriNet:
    init_markup = [1, 1, 1, 1, 1,  # walking position
                   1, 1, 1, 1, 1,  # forks position
                   0, 0, 0, 0, 0,  # philosoph takes left fork
                   0, 0, 0, 0, 0,  # philosoph take right fork
                   0, 0, 0, 0, 0,  # sitting
                   0, 0, 0, 0, 0,  # eating
                   0, 0, 0, 0, 0]  # declined the invitation(service positions)
    net = PetriNet(40, 35, init_markup)

    for i in range(5):
        # can take left fork?
        net.set_input(i, i, 1)
        net.set_input(i, i + 5, 1)
        net.set_output(i, i+10, 1)

        # will take away from the right neighbor?
        net.set_input(i+5, i+10, 1)
        if i != 4:
            net.set_input(i+5, i+11, 1)
        else:
            net.set_input(9, 10, 1)
        net.set_output(i+5, i+15, 1)
        if i != 4:
            net.set_output(i+5, i+1, 1)
        else:
            net.set_output(9, 0, 1)

        # Will decline the invitation?
        net.set_input(i+10, i+10, 1)
        net.set_output(i+10, i+30, 1)
        net.set_output(i+10, i, 1)
        if i != 0:
            net.set_input(i+10, i-1, 1)
            net.set_output(i+10, i-1, 1)
        else:
            net.set_input(10, 4, 1)
            net.set_output(10, 4, 1)

        # Will accept invitation?
        net.set_input(i+15, i+10, 1)
        net.set_output(i+15, i+20, 1)
        if i != 0:
            net.set_input(i+15, i-1, 1)
            net.set_output(i+15, i-1, 1)
        else:
            net.set_input(15, 4, 1)
            net.set_output(15, 4, 1)

        # Start eating
        net.set_input(i+20, i+15, 1)
        net.set_output(i+20, i+25, 1)

        # End of sitting
        net.set_input(i+25, i+20, 1)
        net.set_output(i+25, i, 1)
        net.set_output(i+25, i+5, 1)

        # End of eating
        net.set_input(i+30, i+25, 1)
        net.set_output(i+30, i, 1)
        net.set_output(i+30, i+5, 1)
        if i != 4:
            net.set_output(i+30, i+6, 1)
        else:
            net.set_output(34, 5, 1)

        # Service transition(for declined invitations)
        net.set_input(i+35, i+30, 1)
        net.set_output(i+35, i+5, 1)

    return net


if __name__ == "__main__":
    net = variant4()
    N = 10

    for i in range(4*N-1):
        result = next(net)
        if (i+2) % 4 == 0:
            walking = np.argwhere(result[:5] > 0)[:, 0]
            siting = np.argwhere(result[20:25] > 0)[:, 0]
            eating = np.argwhere(result[25:30] > 0)[:, 0]

            print(" ".join([f"{k}: {str(v + 1)}" for k, v in
                            zip(['walking', 'siting', 'eating'],
                                [walking, siting, eating])]))

if __name__ == "__main__2":
    net = variant2()
    N = 10

    for i in range(3*N-1):
        result = next(net)
        if (i+2) % 3 == 0:
            walking = np.argwhere(result[:5] + result[10:15] > 0)[:, 0]
            eating = np.argwhere(result[15:20] > 0)[:, 0]

            print(" ".join([f"{k}: {str(v + 1)}" for k, v in
                            zip(['walking', 'eating'],
                                [walking, eating])]))


if __name__ == "__main__1":
    net = variant1()
    N = 10

    for i in range(2*N-1):
        result = next(net)
        if i % 2 == 0:
            walking = np.argwhere(result[:5] > 0)[:, 0]
            eating = np.argwhere(result[10:15] > 0)[:, 0]

            print(" ".join([f"{k}: {str(v + 1)}" for k, v in
                            zip(['walking', 'eating'],
                                [walking, eating])]))
