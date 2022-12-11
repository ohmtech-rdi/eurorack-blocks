##############################################################################
#
#     definition.py
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################


{
   'class': 'erb::BoardDefault',
   'include': 'BoardDefault.h',
   'pcb': 'default.kicad_pcb',
   'sch': 'default.kicad_sch',
   'width': 12, # hp
   'pins': {
      'DII1': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(0)',
      },
      'DII2': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(1)',
      },
      'DII3': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(2)',
      },
      'DII4': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(3)',
      },
      'DII5': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(4)',
      },
      'DII6': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(5)',
      },
      'DII7': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(6)',
      },
      'DII8': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(7)',
      },
      'DII9': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(8)',
      },
      'DII10': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(9)',
      },
      'DII11': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(10)',
      },
      'DII12': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(11)',
      },
      'DII13': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(12)',
      },
      'DII14': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(13)',
      },
      'DII15': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(14)',
      },
      'DII16': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(15)',
      },
      'DII17': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(16)',
      },
      'DII18': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(17)',
      },
      'DII19': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(18)',
      },
      'DII20': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(19)',
      },
      'DII21': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(20)',
      },
      'DII22': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(21)',
      },
      'DII23': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(22)',
      },
      'DII24': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(23)',
      },
      'DII25': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(24)',
      },
      'DII26': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(25)',
      },
      'DII27': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(26)',
      },
      'DII28': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(27)',
      },
      'DII29': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(28)',
      },
      'DII30': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(29)',
      },
      'DII31': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(30)',
      },
      'DII32': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(31)',
      },
      'DII33': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(32)',
      },
      'DII34': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(33)',
      },
      'DII35': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(34)',
      },
      'DII36': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(35)',
      },
      'DII37': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(36)',
      },
      'DII38': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(37)',
      },
      'DII39': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(38)',
      },
      'DII40': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(39)',
      },
      'DII41': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(40)',
      },
      'DII42': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(41)',
      },
      'DII43': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(42)',
      },
      'DII44': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(43)',
      },
      'DII45': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(44)',
      },
      'DII46': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(45)',
      },
      'DII47': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(46)',
      },
      'DII48': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(47)',
      },
      'DII49': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(48)',
      },
      'DII50': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(49)',
      },
      'DII51': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(50)',
      },
      'DII52': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(51)',
      },
      'DII53': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(52)',
      },
      'DII54': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(53)',
      },
      'DII55': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(54)',
      },
      'DII56': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(55)',
      },
      'DII57': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(56)',
      },
      'DII58': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(57)',
      },
      'DII59': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(58)',
      },
      'DII60': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(59)',
      },
      'DII61': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(60)',
      },
      'DII62': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(61)',
      },
      'DII63': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(62)',
      },
      'DII64': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(63)',
      },
      'DII65': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(64)',
      },
      'DII66': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(65)',
      },
      'DII67': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(66)',
      },
      'DII68': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(67)',
      },
      'DII69': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(68)',
      },
      'DII70': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(69)',
      },
      'DII71': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(70)',
      },
      'DII72': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(71)',
      },
      'DII73': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(72)',
      },
      'DII74': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(73)',
      },
      'DII75': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(74)',
      },
      'DII76': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(75)',
      },
      'DII77': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(76)',
      },
      'DII78': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(77)',
      },
      'DII79': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(78)',
      },
      'DII80': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(79)',
      },
      'DII81': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(80)',
      },
      'DII82': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(81)',
      },
      'DII83': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(82)',
      },
      'DII84': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(83)',
      },
      'DII85': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(84)',
      },
      'DII86': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(85)',
      },
      'DII87': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(86)',
      },
      'DII88': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(87)',
      },
      'DII89': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(88)',
      },
      'DII90': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(89)',
      },
      'DII91': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(90)',
      },
      'DII92': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(91)',
      },
      'DII93': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(92)',
      },
      'DII94': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(93)',
      },
      'DII95': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(94)',
      },
      'DII96': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(95)',
      },
      'DII97': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(96)',
      },
      'DII98': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(97)',
      },
      'DII99': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(98)',
      },
      'DII100': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(99)',
      },
      'DII101': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(100)',
      },
      'DII102': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(101)',
      },
      'DII103': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(102)',
      },
      'DII104': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(103)',
      },
      'DII105': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(104)',
      },
      'DII106': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(105)',
      },
      'DII107': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(106)',
      },
      'DII108': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(107)',
      },
      'DII109': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(108)',
      },
      'DII110': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(109)',
      },
      'DII111': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(110)',
      },
      'DII112': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(111)',
      },
      'DII113': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(112)',
      },
      'DII114': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(113)',
      },
      'DII115': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(114)',
      },
      'DII116': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(115)',
      },
      'DII117': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(116)',
      },
      'DII118': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(117)',
      },
      'DII119': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(118)',
      },
      'DII120': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(119)',
      },
      'DII121': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(120)',
      },
      'DII122': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(121)',
      },
      'DII123': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(122)',
      },
      'DII124': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(123)',
      },
      'DII125': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(124)',
      },
      'DII126': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(125)',
      },
      'DII127': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(126)',
      },
      'DII128': {
         'accept': ['Button', 'GateIn', 'Switch'],
         'bind': 'dii(127)',
      },
      'ANI1': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(0)',
      },
      'ANI2': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(1)',
      },
      'ANI3': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(2)',
      },
      'ANI4': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(3)',
      },
      'ANI5': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(4)',
      },
      'ANI6': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(5)',
      },
      'ANI7': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(6)',
      },
      'ANI8': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(7)',
      },
      'ANI9': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(8)',
      },
      'ANI10': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(9)',
      },
      'ANI11': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(10)',
      },
      'ANI12': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(11)',
      },
      'ANI13': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(12)',
      },
      'ANI14': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(13)',
      },
      'ANI15': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(14)',
      },
      'ANI16': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(15)',
      },
      'ANI17': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(16)',
      },
      'ANI18': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(17)',
      },
      'ANI19': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(18)',
      },
      'ANI20': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(19)',
      },
      'ANI21': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(20)',
      },
      'ANI22': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(21)',
      },
      'ANI23': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(22)',
      },
      'ANI24': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(23)',
      },
      'ANI25': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(24)',
      },
      'ANI26': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(25)',
      },
      'ANI27': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(26)',
      },
      'ANI28': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(27)',
      },
      'ANI29': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(28)',
      },
      'ANI30': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(29)',
      },
      'ANI31': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(30)',
      },
      'ANI32': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(31)',
      },
      'ANI33': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(32)',
      },
      'ANI34': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(33)',
      },
      'ANI35': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(34)',
      },
      'ANI36': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(35)',
      },
      'ANI37': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(36)',
      },
      'ANI38': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(37)',
      },
      'ANI39': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(38)',
      },
      'ANI40': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(39)',
      },
      'ANI41': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(40)',
      },
      'ANI42': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(41)',
      },
      'ANI43': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(42)',
      },
      'ANI44': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(43)',
      },
      'ANI45': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(44)',
      },
      'ANI46': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(45)',
      },
      'ANI47': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(46)',
      },
      'ANI48': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(47)',
      },
      'ANI49': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(48)',
      },
      'ANI50': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(49)',
      },
      'ANI51': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(50)',
      },
      'ANI52': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(51)',
      },
      'ANI53': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(52)',
      },
      'ANI54': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(53)',
      },
      'ANI55': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(54)',
      },
      'ANI56': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(55)',
      },
      'ANI57': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(56)',
      },
      'ANI58': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(57)',
      },
      'ANI59': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(58)',
      },
      'ANI60': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(59)',
      },
      'ANI61': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(60)',
      },
      'ANI62': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(61)',
      },
      'ANI63': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(62)',
      },
      'ANI64': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(63)',
      },
      'ANI65': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(64)',
      },
      'ANI66': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(65)',
      },
      'ANI67': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(66)',
      },
      'ANI68': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(67)',
      },
      'ANI69': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(68)',
      },
      'ANI70': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(69)',
      },
      'ANI71': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(70)',
      },
      'ANI72': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(71)',
      },
      'ANI73': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(72)',
      },
      'ANI74': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(73)',
      },
      'ANI75': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(74)',
      },
      'ANI76': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(75)',
      },
      'ANI77': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(76)',
      },
      'ANI78': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(77)',
      },
      'ANI79': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(78)',
      },
      'ANI80': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(79)',
      },
      'ANI81': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(80)',
      },
      'ANI82': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(81)',
      },
      'ANI83': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(82)',
      },
      'ANI84': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(83)',
      },
      'ANI85': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(84)',
      },
      'ANI86': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(85)',
      },
      'ANI87': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(86)',
      },
      'ANI88': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(87)',
      },
      'ANI89': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(88)',
      },
      'ANI90': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(89)',
      },
      'ANI91': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(90)',
      },
      'ANI92': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(91)',
      },
      'ANI93': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(92)',
      },
      'ANI94': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(93)',
      },
      'ANI95': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(94)',
      },
      'ANI96': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(95)',
      },
      'ANI97': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(96)',
      },
      'ANI98': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(97)',
      },
      'ANI99': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(98)',
      },
      'ANI100': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(99)',
      },
      'ANI101': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(100)',
      },
      'ANI102': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(101)',
      },
      'ANI103': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(102)',
      },
      'ANI104': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(103)',
      },
      'ANI105': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(104)',
      },
      'ANI106': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(105)',
      },
      'ANI107': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(106)',
      },
      'ANI108': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(107)',
      },
      'ANI109': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(108)',
      },
      'ANI110': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(109)',
      },
      'ANI111': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(110)',
      },
      'ANI112': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(111)',
      },
      'ANI113': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(112)',
      },
      'ANI114': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(113)',
      },
      'ANI115': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(114)',
      },
      'ANI116': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(115)',
      },
      'ANI117': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(116)',
      },
      'ANI118': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(117)',
      },
      'ANI119': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(118)',
      },
      'ANI120': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(119)',
      },
      'ANI121': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(120)',
      },
      'ANI122': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(121)',
      },
      'ANI123': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(122)',
      },
      'ANI124': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(123)',
      },
      'ANI125': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(124)',
      },
      'ANI126': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(125)',
      },
      'ANI127': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(126)',
      },
      'ANI128': {
         'accept': ['CvIn', 'Pot', 'Trim'],
         'bind': 'ani(127)',
      },
      'AUI1': {
         'accept': ['AudioIn'],
         'bind': 'aui(0)',
      },
      'AUI2': {
         'accept': ['AudioIn'],
         'bind': 'aui(1)',
      },
      'AUI3': {
         'accept': ['AudioIn'],
         'bind': 'aui(2)',
      },
      'AUI4': {
         'accept': ['AudioIn'],
         'bind': 'aui(3)',
      },
      'DIO1': {
         'accept': ['GateOut'],
         'bind': 'dio(0)',
      },
      'DIO2': {
         'accept': ['GateOut'],
         'bind': 'dio(1)',
      },
      'DIO3': {
         'accept': ['GateOut'],
         'bind': 'dio(2)',
      },
      'DIO4': {
         'accept': ['GateOut'],
         'bind': 'dio(3)',
      },
      'DIO5': {
         'accept': ['GateOut'],
         'bind': 'dio(4)',
      },
      'DIO6': {
         'accept': ['GateOut'],
         'bind': 'dio(5)',
      },
      'DIO7': {
         'accept': ['GateOut'],
         'bind': 'dio(6)',
      },
      'DIO8': {
         'accept': ['GateOut'],
         'bind': 'dio(7)',
      },
      'DIO9': {
         'accept': ['GateOut'],
         'bind': 'dio(8)',
      },
      'DIO10': {
         'accept': ['GateOut'],
         'bind': 'dio(9)',
      },
      'DIO11': {
         'accept': ['GateOut'],
         'bind': 'dio(10)',
      },
      'DIO12': {
         'accept': ['GateOut'],
         'bind': 'dio(11)',
      },
      'DIO13': {
         'accept': ['GateOut'],
         'bind': 'dio(12)',
      },
      'DIO14': {
         'accept': ['GateOut'],
         'bind': 'dio(13)',
      },
      'DIO15': {
         'accept': ['GateOut'],
         'bind': 'dio(14)',
      },
      'DIO16': {
         'accept': ['GateOut'],
         'bind': 'dio(15)',
      },
      'DIO17': {
         'accept': ['GateOut'],
         'bind': 'dio(16)',
      },
      'DIO18': {
         'accept': ['GateOut'],
         'bind': 'dio(17)',
      },
      'DIO19': {
         'accept': ['GateOut'],
         'bind': 'dio(18)',
      },
      'DIO20': {
         'accept': ['GateOut'],
         'bind': 'dio(19)',
      },
      'DIO21': {
         'accept': ['GateOut'],
         'bind': 'dio(20)',
      },
      'DIO22': {
         'accept': ['GateOut'],
         'bind': 'dio(21)',
      },
      'DIO23': {
         'accept': ['GateOut'],
         'bind': 'dio(22)',
      },
      'DIO24': {
         'accept': ['GateOut'],
         'bind': 'dio(23)',
      },
      'DIO25': {
         'accept': ['GateOut'],
         'bind': 'dio(24)',
      },
      'DIO26': {
         'accept': ['GateOut'],
         'bind': 'dio(25)',
      },
      'DIO27': {
         'accept': ['GateOut'],
         'bind': 'dio(26)',
      },
      'DIO28': {
         'accept': ['GateOut'],
         'bind': 'dio(27)',
      },
      'DIO29': {
         'accept': ['GateOut'],
         'bind': 'dio(28)',
      },
      'DIO30': {
         'accept': ['GateOut'],
         'bind': 'dio(29)',
      },
      'DIO31': {
         'accept': ['GateOut'],
         'bind': 'dio(30)',
      },
      'DIO32': {
         'accept': ['GateOut'],
         'bind': 'dio(31)',
      },
      'DIO33': {
         'accept': ['GateOut'],
         'bind': 'dio(32)',
      },
      'DIO34': {
         'accept': ['GateOut'],
         'bind': 'dio(33)',
      },
      'DIO35': {
         'accept': ['GateOut'],
         'bind': 'dio(34)',
      },
      'DIO36': {
         'accept': ['GateOut'],
         'bind': 'dio(35)',
      },
      'DIO37': {
         'accept': ['GateOut'],
         'bind': 'dio(36)',
      },
      'DIO38': {
         'accept': ['GateOut'],
         'bind': 'dio(37)',
      },
      'DIO39': {
         'accept': ['GateOut'],
         'bind': 'dio(38)',
      },
      'DIO40': {
         'accept': ['GateOut'],
         'bind': 'dio(39)',
      },
      'DIO41': {
         'accept': ['GateOut'],
         'bind': 'dio(40)',
      },
      'DIO42': {
         'accept': ['GateOut'],
         'bind': 'dio(41)',
      },
      'DIO43': {
         'accept': ['GateOut'],
         'bind': 'dio(42)',
      },
      'DIO44': {
         'accept': ['GateOut'],
         'bind': 'dio(43)',
      },
      'DIO45': {
         'accept': ['GateOut'],
         'bind': 'dio(44)',
      },
      'DIO46': {
         'accept': ['GateOut'],
         'bind': 'dio(45)',
      },
      'DIO47': {
         'accept': ['GateOut'],
         'bind': 'dio(46)',
      },
      'DIO48': {
         'accept': ['GateOut'],
         'bind': 'dio(47)',
      },
      'DIO49': {
         'accept': ['GateOut'],
         'bind': 'dio(48)',
      },
      'DIO50': {
         'accept': ['GateOut'],
         'bind': 'dio(49)',
      },
      'DIO51': {
         'accept': ['GateOut'],
         'bind': 'dio(50)',
      },
      'DIO52': {
         'accept': ['GateOut'],
         'bind': 'dio(51)',
      },
      'DIO53': {
         'accept': ['GateOut'],
         'bind': 'dio(52)',
      },
      'DIO54': {
         'accept': ['GateOut'],
         'bind': 'dio(53)',
      },
      'DIO55': {
         'accept': ['GateOut'],
         'bind': 'dio(54)',
      },
      'DIO56': {
         'accept': ['GateOut'],
         'bind': 'dio(55)',
      },
      'DIO57': {
         'accept': ['GateOut'],
         'bind': 'dio(56)',
      },
      'DIO58': {
         'accept': ['GateOut'],
         'bind': 'dio(57)',
      },
      'DIO59': {
         'accept': ['GateOut'],
         'bind': 'dio(58)',
      },
      'DIO60': {
         'accept': ['GateOut'],
         'bind': 'dio(59)',
      },
      'DIO61': {
         'accept': ['GateOut'],
         'bind': 'dio(60)',
      },
      'DIO62': {
         'accept': ['GateOut'],
         'bind': 'dio(61)',
      },
      'DIO63': {
         'accept': ['GateOut'],
         'bind': 'dio(62)',
      },
      'DIO64': {
         'accept': ['GateOut'],
         'bind': 'dio(63)',
      },
      'DIO65': {
         'accept': ['GateOut'],
         'bind': 'dio(64)',
      },
      'DIO66': {
         'accept': ['GateOut'],
         'bind': 'dio(65)',
      },
      'DIO67': {
         'accept': ['GateOut'],
         'bind': 'dio(66)',
      },
      'DIO68': {
         'accept': ['GateOut'],
         'bind': 'dio(67)',
      },
      'DIO69': {
         'accept': ['GateOut'],
         'bind': 'dio(68)',
      },
      'DIO70': {
         'accept': ['GateOut'],
         'bind': 'dio(69)',
      },
      'DIO71': {
         'accept': ['GateOut'],
         'bind': 'dio(70)',
      },
      'DIO72': {
         'accept': ['GateOut'],
         'bind': 'dio(71)',
      },
      'DIO73': {
         'accept': ['GateOut'],
         'bind': 'dio(72)',
      },
      'DIO74': {
         'accept': ['GateOut'],
         'bind': 'dio(73)',
      },
      'DIO75': {
         'accept': ['GateOut'],
         'bind': 'dio(74)',
      },
      'DIO76': {
         'accept': ['GateOut'],
         'bind': 'dio(75)',
      },
      'DIO77': {
         'accept': ['GateOut'],
         'bind': 'dio(76)',
      },
      'DIO78': {
         'accept': ['GateOut'],
         'bind': 'dio(77)',
      },
      'DIO79': {
         'accept': ['GateOut'],
         'bind': 'dio(78)',
      },
      'DIO80': {
         'accept': ['GateOut'],
         'bind': 'dio(79)',
      },
      'DIO81': {
         'accept': ['GateOut'],
         'bind': 'dio(80)',
      },
      'DIO82': {
         'accept': ['GateOut'],
         'bind': 'dio(81)',
      },
      'DIO83': {
         'accept': ['GateOut'],
         'bind': 'dio(82)',
      },
      'DIO84': {
         'accept': ['GateOut'],
         'bind': 'dio(83)',
      },
      'DIO85': {
         'accept': ['GateOut'],
         'bind': 'dio(84)',
      },
      'DIO86': {
         'accept': ['GateOut'],
         'bind': 'dio(85)',
      },
      'DIO87': {
         'accept': ['GateOut'],
         'bind': 'dio(86)',
      },
      'DIO88': {
         'accept': ['GateOut'],
         'bind': 'dio(87)',
      },
      'DIO89': {
         'accept': ['GateOut'],
         'bind': 'dio(88)',
      },
      'DIO90': {
         'accept': ['GateOut'],
         'bind': 'dio(89)',
      },
      'DIO91': {
         'accept': ['GateOut'],
         'bind': 'dio(90)',
      },
      'DIO92': {
         'accept': ['GateOut'],
         'bind': 'dio(91)',
      },
      'DIO93': {
         'accept': ['GateOut'],
         'bind': 'dio(92)',
      },
      'DIO94': {
         'accept': ['GateOut'],
         'bind': 'dio(93)',
      },
      'DIO95': {
         'accept': ['GateOut'],
         'bind': 'dio(94)',
      },
      'DIO96': {
         'accept': ['GateOut'],
         'bind': 'dio(95)',
      },
      'DIO97': {
         'accept': ['GateOut'],
         'bind': 'dio(96)',
      },
      'DIO98': {
         'accept': ['GateOut'],
         'bind': 'dio(97)',
      },
      'DIO99': {
         'accept': ['GateOut'],
         'bind': 'dio(98)',
      },
      'DIO100': {
         'accept': ['GateOut'],
         'bind': 'dio(99)',
      },
      'DIO101': {
         'accept': ['GateOut'],
         'bind': 'dio(100)',
      },
      'DIO102': {
         'accept': ['GateOut'],
         'bind': 'dio(101)',
      },
      'DIO103': {
         'accept': ['GateOut'],
         'bind': 'dio(102)',
      },
      'DIO104': {
         'accept': ['GateOut'],
         'bind': 'dio(103)',
      },
      'DIO105': {
         'accept': ['GateOut'],
         'bind': 'dio(104)',
      },
      'DIO106': {
         'accept': ['GateOut'],
         'bind': 'dio(105)',
      },
      'DIO107': {
         'accept': ['GateOut'],
         'bind': 'dio(106)',
      },
      'DIO108': {
         'accept': ['GateOut'],
         'bind': 'dio(107)',
      },
      'DIO109': {
         'accept': ['GateOut'],
         'bind': 'dio(108)',
      },
      'DIO110': {
         'accept': ['GateOut'],
         'bind': 'dio(109)',
      },
      'DIO111': {
         'accept': ['GateOut'],
         'bind': 'dio(110)',
      },
      'DIO112': {
         'accept': ['GateOut'],
         'bind': 'dio(111)',
      },
      'DIO113': {
         'accept': ['GateOut'],
         'bind': 'dio(112)',
      },
      'DIO114': {
         'accept': ['GateOut'],
         'bind': 'dio(113)',
      },
      'DIO115': {
         'accept': ['GateOut'],
         'bind': 'dio(114)',
      },
      'DIO116': {
         'accept': ['GateOut'],
         'bind': 'dio(115)',
      },
      'DIO117': {
         'accept': ['GateOut'],
         'bind': 'dio(116)',
      },
      'DIO118': {
         'accept': ['GateOut'],
         'bind': 'dio(117)',
      },
      'DIO119': {
         'accept': ['GateOut'],
         'bind': 'dio(118)',
      },
      'DIO120': {
         'accept': ['GateOut'],
         'bind': 'dio(119)',
      },
      'DIO121': {
         'accept': ['GateOut'],
         'bind': 'dio(120)',
      },
      'DIO122': {
         'accept': ['GateOut'],
         'bind': 'dio(121)',
      },
      'DIO123': {
         'accept': ['GateOut'],
         'bind': 'dio(122)',
      },
      'DIO124': {
         'accept': ['GateOut'],
         'bind': 'dio(123)',
      },
      'DIO125': {
         'accept': ['GateOut'],
         'bind': 'dio(124)',
      },
      'DIO126': {
         'accept': ['GateOut'],
         'bind': 'dio(125)',
      },
      'DIO127': {
         'accept': ['GateOut'],
         'bind': 'dio(126)',
      },
      'DIO128': {
         'accept': ['GateOut'],
         'bind': 'dio(127)',
      },
      'ANO1': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(0)',
      },
      'ANO2': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(1)',
      },
      'ANO3': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(2)',
      },
      'ANO4': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(3)',
      },
      'ANO5': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(4)',
      },
      'ANO6': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(5)',
      },
      'ANO7': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(6)',
      },
      'ANO8': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(7)',
      },
      'ANO9': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(8)',
      },
      'ANO10': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(9)',
      },
      'ANO11': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(10)',
      },
      'ANO12': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(11)',
      },
      'ANO13': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(12)',
      },
      'ANO14': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(13)',
      },
      'ANO15': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(14)',
      },
      'ANO16': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(15)',
      },
      'ANO17': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(16)',
      },
      'ANO18': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(17)',
      },
      'ANO19': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(18)',
      },
      'ANO20': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(19)',
      },
      'ANO21': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(20)',
      },
      'ANO22': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(21)',
      },
      'ANO23': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(22)',
      },
      'ANO24': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(23)',
      },
      'ANO25': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(24)',
      },
      'ANO26': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(25)',
      },
      'ANO27': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(26)',
      },
      'ANO28': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(27)',
      },
      'ANO29': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(28)',
      },
      'ANO30': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(29)',
      },
      'ANO31': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(30)',
      },
      'ANO32': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(31)',
      },
      'ANO33': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(32)',
      },
      'ANO34': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(33)',
      },
      'ANO35': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(34)',
      },
      'ANO36': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(35)',
      },
      'ANO37': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(36)',
      },
      'ANO38': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(37)',
      },
      'ANO39': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(38)',
      },
      'ANO40': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(39)',
      },
      'ANO41': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(40)',
      },
      'ANO42': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(41)',
      },
      'ANO43': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(42)',
      },
      'ANO44': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(43)',
      },
      'ANO45': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(44)',
      },
      'ANO46': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(45)',
      },
      'ANO47': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(46)',
      },
      'ANO48': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(47)',
      },
      'ANO49': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(48)',
      },
      'ANO50': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(49)',
      },
      'ANO51': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(50)',
      },
      'ANO52': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(51)',
      },
      'ANO53': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(52)',
      },
      'ANO54': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(53)',
      },
      'ANO55': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(54)',
      },
      'ANO56': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(55)',
      },
      'ANO57': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(56)',
      },
      'ANO58': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(57)',
      },
      'ANO59': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(58)',
      },
      'ANO60': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(59)',
      },
      'ANO61': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(60)',
      },
      'ANO62': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(61)',
      },
      'ANO63': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(62)',
      },
      'ANO64': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(63)',
      },
      'ANO65': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(64)',
      },
      'ANO66': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(65)',
      },
      'ANO67': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(66)',
      },
      'ANO68': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(67)',
      },
      'ANO69': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(68)',
      },
      'ANO70': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(69)',
      },
      'ANO71': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(70)',
      },
      'ANO72': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(71)',
      },
      'ANO73': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(72)',
      },
      'ANO74': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(73)',
      },
      'ANO75': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(74)',
      },
      'ANO76': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(75)',
      },
      'ANO77': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(76)',
      },
      'ANO78': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(77)',
      },
      'ANO79': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(78)',
      },
      'ANO80': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(79)',
      },
      'ANO81': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(80)',
      },
      'ANO82': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(81)',
      },
      'ANO83': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(82)',
      },
      'ANO84': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(83)',
      },
      'ANO85': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(84)',
      },
      'ANO86': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(85)',
      },
      'ANO87': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(86)',
      },
      'ANO88': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(87)',
      },
      'ANO89': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(88)',
      },
      'ANO90': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(89)',
      },
      'ANO91': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(90)',
      },
      'ANO92': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(91)',
      },
      'ANO93': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(92)',
      },
      'ANO94': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(93)',
      },
      'ANO95': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(94)',
      },
      'ANO96': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(95)',
      },
      'ANO97': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(96)',
      },
      'ANO98': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(97)',
      },
      'ANO99': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(98)',
      },
      'ANO100': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(99)',
      },
      'ANO101': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(100)',
      },
      'ANO102': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(101)',
      },
      'ANO103': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(102)',
      },
      'ANO104': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(103)',
      },
      'ANO105': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(104)',
      },
      'ANO106': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(105)',
      },
      'ANO107': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(106)',
      },
      'ANO108': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(107)',
      },
      'ANO109': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(108)',
      },
      'ANO110': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(109)',
      },
      'ANO111': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(110)',
      },
      'ANO112': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(111)',
      },
      'ANO113': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(112)',
      },
      'ANO114': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(113)',
      },
      'ANO115': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(114)',
      },
      'ANO116': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(115)',
      },
      'ANO117': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(116)',
      },
      'ANO118': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(117)',
      },
      'ANO119': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(118)',
      },
      'ANO120': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(119)',
      },
      'ANO121': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(120)',
      },
      'ANO122': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(121)',
      },
      'ANO123': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(122)',
      },
      'ANO124': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(123)',
      },
      'ANO125': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(124)',
      },
      'ANO126': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(125)',
      },
      'ANO127': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(126)',
      },
      'ANO128': {
         'type': 'pwm', # Led*
         'accept': ['CvOut', 'Led', 'LedBi', 'LedRgb'],
         'bind': 'ano(127)',
      },
      'AUO1': {
         'accept': ['AudioOut'],
         'bind': 'auo(0)',
      },
      'AUO2': {
         'accept': ['AudioOut'],
         'bind': 'auo(1)',
      },
      'AUO3': {
         'accept': ['AudioOut'],
         'bind': 'auo(2)',
      },
      'AUO4': {
         'accept': ['AudioOut'],
         'bind': 'auo(3)',
      },
   },
   'kinds': {
      'CvIn': {'pools': ['ANI']},
      'CvOut': {'pools': ['ANO']},
      'GateOut': {'pools': ['DIO']},
      'AudioIn': {'pools': ['AUI']},
      'AudioOut': {'pools': ['AUO']},
      'Led': {'pools': ['ANO']},
      'LedBi': {'pools': ['ANO', 'ANO']},
      'LedRgb': {'pools': ['ANO', 'ANO', 'ANO']},
      'Pot': {'pools': ['ANI']},
      'Trim': {'pools': ['ANI']},
      'Button': {'pools': ['DII']},
      'GateIn': {'pools': ['DII']},
      'Switch': {'pools': ['DII', 'DII']},
   },
   'pools': {
      'DII': ['DII1', 'DII2', 'DII3', 'DII4', 'DII5', 'DII6', 'DII7', 'DII8', 'DII9', 'DII10', 'DII11', 'DII12', 'DII13', 'DII14', 'DII15', 'DII16', 'DII17', 'DII18', 'DII19', 'DII20', 'DII21', 'DII22', 'DII23', 'DII24', 'DII25', 'DII26', 'DII27', 'DII28', 'DII29', 'DII30', 'DII31', 'DII32', 'DII33', 'DII34', 'DII35', 'DII36', 'DII37', 'DII38', 'DII39', 'DII40', 'DII41', 'DII42', 'DII43', 'DII44', 'DII45', 'DII46', 'DII47', 'DII48', 'DII49', 'DII50', 'DII51', 'DII52', 'DII53', 'DII54', 'DII55', 'DII56', 'DII57', 'DII58', 'DII59', 'DII60', 'DII61', 'DII62', 'DII63', 'DII64', 'DII65', 'DII66', 'DII67', 'DII68', 'DII69', 'DII70', 'DII71', 'DII72', 'DII73', 'DII74', 'DII75', 'DII76', 'DII77', 'DII78', 'DII79', 'DII80', 'DII81', 'DII82', 'DII83', 'DII84', 'DII85', 'DII86', 'DII87', 'DII88', 'DII89', 'DII90', 'DII91', 'DII92', 'DII93', 'DII94', 'DII95', 'DII96', 'DII97', 'DII98', 'DII99', 'DII100', 'DII101', 'DII102', 'DII103', 'DII104', 'DII105', 'DII106', 'DII107', 'DII108', 'DII109', 'DII110', 'DII111', 'DII112', 'DII113', 'DII114', 'DII115', 'DII116', 'DII117', 'DII118', 'DII119', 'DII120', 'DII121', 'DII122', 'DII123', 'DII124', 'DII125', 'DII126', 'DII127', 'DII128'],
      'ANI': ['ANI1', 'ANI2', 'ANI3', 'ANI4', 'ANI5', 'ANI6', 'ANI7', 'ANI8', 'ANI9', 'ANI10', 'ANI11', 'ANI12', 'ANI13', 'ANI14', 'ANI15', 'ANI16', 'ANI17', 'ANI18', 'ANI19', 'ANI20', 'ANI21', 'ANI22', 'ANI23', 'ANI24', 'ANI25', 'ANI26', 'ANI27', 'ANI28', 'ANI29', 'ANI30', 'ANI31', 'ANI32', 'ANI33', 'ANI34', 'ANI35', 'ANI36', 'ANI37', 'ANI38', 'ANI39', 'ANI40', 'ANI41', 'ANI42', 'ANI43', 'ANI44', 'ANI45', 'ANI46', 'ANI47', 'ANI48', 'ANI49', 'ANI50', 'ANI51', 'ANI52', 'ANI53', 'ANI54', 'ANI55', 'ANI56', 'ANI57', 'ANI58', 'ANI59', 'ANI60', 'ANI61', 'ANI62', 'ANI63', 'ANI64', 'ANI65', 'ANI66', 'ANI67', 'ANI68', 'ANI69', 'ANI70', 'ANI71', 'ANI72', 'ANI73', 'ANI74', 'ANI75', 'ANI76', 'ANI77', 'ANI78', 'ANI79', 'ANI80', 'ANI81', 'ANI82', 'ANI83', 'ANI84', 'ANI85', 'ANI86', 'ANI87', 'ANI88', 'ANI89', 'ANI90', 'ANI91', 'ANI92', 'ANI93', 'ANI94', 'ANI95', 'ANI96', 'ANI97', 'ANI98', 'ANI99', 'ANI100', 'ANI101', 'ANI102', 'ANI103', 'ANI104', 'ANI105', 'ANI106', 'ANI107', 'ANI108', 'ANI109', 'ANI110', 'ANI111', 'ANI112', 'ANI113', 'ANI114', 'ANI115', 'ANI116', 'ANI117', 'ANI118', 'ANI119', 'ANI120', 'ANI121', 'ANI122', 'ANI123', 'ANI124', 'ANI125', 'ANI126', 'ANI127', 'ANI128'],
      'AUI': ['AUI1', 'AUI2', 'AUI3', 'AUI4'],
      'DIO': ['DIO1', 'DIO2', 'DIO3', 'DIO4', 'DIO5', 'DIO6', 'DIO7', 'DIO8', 'DIO9', 'DIO10', 'DIO11', 'DIO12', 'DIO13', 'DIO14', 'DIO15', 'DIO16', 'DIO17', 'DIO18', 'DIO19', 'DIO20', 'DIO21', 'DIO22', 'DIO23', 'DIO24', 'DIO25', 'DIO26', 'DIO27', 'DIO28', 'DIO29', 'DIO30', 'DIO31', 'DIO32', 'DIO33', 'DIO34', 'DIO35', 'DIO36', 'DIO37', 'DIO38', 'DIO39', 'DIO40', 'DIO41', 'DIO42', 'DIO43', 'DIO44', 'DIO45', 'DIO46', 'DIO47', 'DIO48', 'DIO49', 'DIO50', 'DIO51', 'DIO52', 'DIO53', 'DIO54', 'DIO55', 'DIO56', 'DIO57', 'DIO58', 'DIO59', 'DIO60', 'DIO61', 'DIO62', 'DIO63', 'DIO64', 'DIO65', 'DIO66', 'DIO67', 'DIO68', 'DIO69', 'DIO70', 'DIO71', 'DIO72', 'DIO73', 'DIO74', 'DIO75', 'DIO76', 'DIO77', 'DIO78', 'DIO79', 'DIO80', 'DIO81', 'DIO82', 'DIO83', 'DIO84', 'DIO85', 'DIO86', 'DIO87', 'DIO88', 'DIO89', 'DIO90', 'DIO91', 'DIO92', 'DIO93', 'DIO94', 'DIO95', 'DIO96', 'DIO97', 'DIO98', 'DIO99', 'DIO100', 'DIO101', 'DIO102', 'DIO103', 'DIO104', 'DIO105', 'DIO106', 'DIO107', 'DIO108', 'DIO109', 'DIO110', 'DIO111', 'DIO112', 'DIO113', 'DIO114', 'DIO115', 'DIO116', 'DIO117', 'DIO118', 'DIO119', 'DIO120', 'DIO121', 'DIO122', 'DIO123', 'DIO124', 'DIO125', 'DIO126', 'DIO127', 'DIO128'],
      'ANO': ['ANO1', 'ANO2', 'ANO3', 'ANO4', 'ANO5', 'ANO6', 'ANO7', 'ANO8', 'ANO9', 'ANO10', 'ANO11', 'ANO12', 'ANO13', 'ANO14', 'ANO15', 'ANO16', 'ANO17', 'ANO18', 'ANO19', 'ANO20', 'ANO21', 'ANO22', 'ANO23', 'ANO24', 'ANO25', 'ANO26', 'ANO27', 'ANO28', 'ANO29', 'ANO30', 'ANO31', 'ANO32', 'ANO33', 'ANO34', 'ANO35', 'ANO36', 'ANO37', 'ANO38', 'ANO39', 'ANO40', 'ANO41', 'ANO42', 'ANO43', 'ANO44', 'ANO45', 'ANO46', 'ANO47', 'ANO48', 'ANO49', 'ANO50', 'ANO51', 'ANO52', 'ANO53', 'ANO54', 'ANO55', 'ANO56', 'ANO57', 'ANO58', 'ANO59', 'ANO60', 'ANO61', 'ANO62', 'ANO63', 'ANO64', 'ANO65', 'ANO66', 'ANO67', 'ANO68', 'ANO69', 'ANO70', 'ANO71', 'ANO72', 'ANO73', 'ANO74', 'ANO75', 'ANO76', 'ANO77', 'ANO78', 'ANO79', 'ANO80', 'ANO81', 'ANO82', 'ANO83', 'ANO84', 'ANO85', 'ANO86', 'ANO87', 'ANO88', 'ANO89', 'ANO90', 'ANO91', 'ANO92', 'ANO93', 'ANO94', 'ANO95', 'ANO96', 'ANO97', 'ANO98', 'ANO99', 'ANO100', 'ANO101', 'ANO102', 'ANO103', 'ANO104', 'ANO105', 'ANO106', 'ANO107', 'ANO108', 'ANO109', 'ANO110', 'ANO111', 'ANO112', 'ANO113', 'ANO114', 'ANO115', 'ANO116', 'ANO117', 'ANO118', 'ANO119', 'ANO120', 'ANO121', 'ANO122', 'ANO123', 'ANO124', 'ANO125', 'ANO126', 'ANO127', 'ANO128'],
      'AUO': ['AUO1', 'AUO2', 'AUO3', 'AUO4'],
   },
}
