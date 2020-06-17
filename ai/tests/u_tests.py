import unittest
from zappy_ai.trantorian import Trantorian
import socket

class TrantorianElevationTestCase (unittest.TestCase):
    def setUp(self):
        sockfd = socket.socket(socket.AF_INET, socket.SOCK_STREAM, socket.IPPROTO_IP)
        self.trantorian = Trantorian("toto", sockfd)

    def test_no_elevation(self):
        self.trantorian.check_ressources()
        self.assertEqual(self.trantorian.level, 1)

    def test_elevation_1_to_2(self):
        self.trantorian.player_gathered = 1
        print(self.trantorian.level)
        self.trantorian.stones = { "linemate": 1, "deraumere": 0, "sibur": 0,
                "mendiane": 0, "phiras": 0, "thystame": 0 }
        self.trantorian.check_ressources()
        self.assertEqual(self.trantorian.level, 2)

    def test_elevation_2_to_3(self):
        self.trantorian.player_gathered = 2
        self.trantorian.level = 2
        self.trantorian.stones = { "linemate": 1, "deraumere": 1, "sibur": 1,
                "mendiane": 0, "phiras": 0, "thystame": 0 }
        self.trantorian.check_ressources()
        self.assertEqual(self.trantorian.level, 3)
        
    def test_elevation_3_to_4(self):
        self.trantorian.player_gathered = 2
        self.trantorian.level = 3
        self.trantorian.stones = { "linemate": 2, "deraumere": 0, "sibur": 1,
                "mendiane": 0, "phiras": 2, "thystame": 0 }
        self.trantorian.check_ressources()
        self.assertEqual(self.trantorian.level, 4)

    def test_elevation_4_to_5(self):
        self.trantorian.player_gathered = 4
        self.trantorian.level = 4
        self.trantorian.stones = { "linemate": 1, "deraumere": 1, "sibur": 2,
                "mendiane": 0, "phiras": 1, "thystame": 2 }
        self.trantorian.check_ressources()
        self.assertEqual(self.trantorian.level, 5)

    def test_elevation_5_to_6(self):
        self.trantorian.player_gathered = 4
        self.trantorian.level = 5
        self.trantorian.stones = { "linemate": 1, "deraumere": 2, "sibur": 1,
                "mendiane": 3, "phiras": 0, "thystame": 0 }
        self.trantorian.check_ressources()
        self.assertEqual(self.trantorian.level, 6)

    def test_elevation_6_to_7(self):
        self.trantorian.player_gathered = 6
        self.trantorian.level = 6
        self.trantorian.stones = { "linemate": 1, "deraumere": 2, "sibur": 3,
                "mendiane": 0, "phiras": 1, "thystame": 0 }
        self.trantorian.check_ressources()
        self.assertEqual(self.trantorian.level, 7)

    def test_elevation_7_to_8(self):
        self.trantorian.player_gathered = 6
        self.trantorian.level = 7
        self.trantorian.stones = { "linemate": 2, "deraumere": 2, "sibur": 2,
                "mendiane": 2, "phiras": 2, "thystame": 1 }
        self.trantorian.check_ressources()
        self.assertEqual(self.trantorian.level, 8)

