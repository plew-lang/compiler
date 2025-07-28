// Generated from ./grammer/Plew.g4 by ANTLR 4.13.2
// noinspection ES6UnusedImports,JSUnusedGlobalSymbols,JSUnusedLocalSymbols
import {
	ATN,
	ATNDeserializer,
	CharStream,
	DecisionState, DFA,
	Lexer,
	LexerATNSimulator,
	RuleContext,
	PredictionContextCache,
	Token
} from "antlr4";
export default class PlewLexer extends Lexer {
	public static readonly T__0 = 1;
	public static readonly T__1 = 2;
	public static readonly T__2 = 3;
	public static readonly T__3 = 4;
	public static readonly T__4 = 5;
	public static readonly T__5 = 6;
	public static readonly T__6 = 7;
	public static readonly T__7 = 8;
	public static readonly T__8 = 9;
	public static readonly T__9 = 10;
	public static readonly T__10 = 11;
	public static readonly T__11 = 12;
	public static readonly T__12 = 13;
	public static readonly NEWLINE = 14;
	public static readonly DIGIT = 15;
	public static readonly SNAKE_CASE = 16;
	public static readonly PASCAL_CASE = 17;
	public static readonly ADD_OP = 18;
	public static readonly MUL_OP = 19;
	public static readonly UNARY_OP = 20;
	public static readonly EOF = Token.EOF;

	public static readonly channelNames: string[] = [ "DEFAULT_TOKEN_CHANNEL", "HIDDEN" ];
	public static readonly literalNames: (string | null)[] = [ null, "'fn'", 
                                                            "'('", "')'", 
                                                            "'->'", "','", 
                                                            "':'", "'{'", 
                                                            "'}'", "'return'", 
                                                            "'.'", "'\"'", 
                                                            "'true'", "'false'", 
                                                            "'\\n'" ];
	public static readonly symbolicNames: (string | null)[] = [ null, null, 
                                                             null, null, 
                                                             null, null, 
                                                             null, null, 
                                                             null, null, 
                                                             null, null, 
                                                             null, null, 
                                                             "NEWLINE", 
                                                             "DIGIT", "SNAKE_CASE", 
                                                             "PASCAL_CASE", 
                                                             "ADD_OP", "MUL_OP", 
                                                             "UNARY_OP" ];
	public static readonly modeNames: string[] = [ "DEFAULT_MODE", ];

	public static readonly ruleNames: string[] = [
		"T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
		"T__9", "T__10", "T__11", "T__12", "NEWLINE", "DIGIT", "SNAKE_CASE", "PASCAL_CASE", 
		"ADD_OP", "MUL_OP", "UNARY_OP",
	];


	constructor(input: CharStream) {
		super(input);
		this._interp = new LexerATNSimulator(this, PlewLexer._ATN, PlewLexer.DecisionsToDFA, new PredictionContextCache());
	}

	public get grammarFileName(): string { return "Plew.g4"; }

	public get literalNames(): (string | null)[] { return PlewLexer.literalNames; }
	public get symbolicNames(): (string | null)[] { return PlewLexer.symbolicNames; }
	public get ruleNames(): string[] { return PlewLexer.ruleNames; }

	public get serializedATN(): number[] { return PlewLexer._serializedATN; }

	public get channelNames(): string[] { return PlewLexer.channelNames; }

	public get modeNames(): string[] { return PlewLexer.modeNames; }

	public static readonly _serializedATN: number[] = [4,0,20,105,6,-1,2,0,
	7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,7,7,7,2,8,7,8,2,9,
	7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,14,2,15,7,15,2,16,7,
	16,2,17,7,17,2,18,7,18,2,19,7,19,1,0,1,0,1,0,1,1,1,1,1,2,1,2,1,3,1,3,1,
	3,1,4,1,4,1,5,1,5,1,6,1,6,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,9,1,9,1,
	10,1,10,1,11,1,11,1,11,1,11,1,11,1,12,1,12,1,12,1,12,1,12,1,12,1,13,1,13,
	1,14,1,14,1,15,1,15,5,15,88,8,15,10,15,12,15,91,9,15,1,16,1,16,5,16,95,
	8,16,10,16,12,16,98,9,16,1,17,1,17,1,18,1,18,1,19,1,19,0,0,20,1,1,3,2,5,
	3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,27,14,29,15,31,16,
	33,17,35,18,37,19,39,20,1,0,8,1,0,48,57,1,0,97,122,3,0,48,57,95,95,97,122,
	1,0,65,90,3,0,48,57,65,90,97,122,2,0,43,43,45,45,2,0,42,42,47,47,2,0,33,
	33,45,45,106,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,
	0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,
	1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,0,31,1,0,0,
	0,0,33,1,0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,1,0,0,0,1,41,1,0,0,0,3,44,
	1,0,0,0,5,46,1,0,0,0,7,48,1,0,0,0,9,51,1,0,0,0,11,53,1,0,0,0,13,55,1,0,
	0,0,15,57,1,0,0,0,17,59,1,0,0,0,19,66,1,0,0,0,21,68,1,0,0,0,23,70,1,0,0,
	0,25,75,1,0,0,0,27,81,1,0,0,0,29,83,1,0,0,0,31,85,1,0,0,0,33,92,1,0,0,0,
	35,99,1,0,0,0,37,101,1,0,0,0,39,103,1,0,0,0,41,42,5,102,0,0,42,43,5,110,
	0,0,43,2,1,0,0,0,44,45,5,40,0,0,45,4,1,0,0,0,46,47,5,41,0,0,47,6,1,0,0,
	0,48,49,5,45,0,0,49,50,5,62,0,0,50,8,1,0,0,0,51,52,5,44,0,0,52,10,1,0,0,
	0,53,54,5,58,0,0,54,12,1,0,0,0,55,56,5,123,0,0,56,14,1,0,0,0,57,58,5,125,
	0,0,58,16,1,0,0,0,59,60,5,114,0,0,60,61,5,101,0,0,61,62,5,116,0,0,62,63,
	5,117,0,0,63,64,5,114,0,0,64,65,5,110,0,0,65,18,1,0,0,0,66,67,5,46,0,0,
	67,20,1,0,0,0,68,69,5,34,0,0,69,22,1,0,0,0,70,71,5,116,0,0,71,72,5,114,
	0,0,72,73,5,117,0,0,73,74,5,101,0,0,74,24,1,0,0,0,75,76,5,102,0,0,76,77,
	5,97,0,0,77,78,5,108,0,0,78,79,5,115,0,0,79,80,5,101,0,0,80,26,1,0,0,0,
	81,82,5,10,0,0,82,28,1,0,0,0,83,84,7,0,0,0,84,30,1,0,0,0,85,89,7,1,0,0,
	86,88,7,2,0,0,87,86,1,0,0,0,88,91,1,0,0,0,89,87,1,0,0,0,89,90,1,0,0,0,90,
	32,1,0,0,0,91,89,1,0,0,0,92,96,7,3,0,0,93,95,7,4,0,0,94,93,1,0,0,0,95,98,
	1,0,0,0,96,94,1,0,0,0,96,97,1,0,0,0,97,34,1,0,0,0,98,96,1,0,0,0,99,100,
	7,5,0,0,100,36,1,0,0,0,101,102,7,6,0,0,102,38,1,0,0,0,103,104,7,7,0,0,104,
	40,1,0,0,0,3,0,89,96,0];

	private static __ATN: ATN;
	public static get _ATN(): ATN {
		if (!PlewLexer.__ATN) {
			PlewLexer.__ATN = new ATNDeserializer().deserialize(PlewLexer._serializedATN);
		}

		return PlewLexer.__ATN;
	}


	static DecisionsToDFA = PlewLexer._ATN.decisionToState.map( (ds: DecisionState, index: number) => new DFA(ds, index) );
}