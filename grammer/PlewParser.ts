// Generated from ./grammer/Plew.g4 by ANTLR 4.13.2
// noinspection ES6UnusedImports,JSUnusedGlobalSymbols,JSUnusedLocalSymbols

import {
	ATN,
	ATNDeserializer, DecisionState, DFA, FailedPredicateException,
	RecognitionException, NoViableAltException, BailErrorStrategy,
	Parser, ParserATNSimulator,
	RuleContext, ParserRuleContext, PredictionMode, PredictionContextCache,
	TerminalNode, RuleNode,
	Token, TokenStream,
	Interval, IntervalSet
} from 'antlr4';
import PlewListener from "./PlewListener.js";
// for running tests with parameters, TODO: discuss strategy for typed parameters in CI
// eslint-disable-next-line no-unused-vars
type int = number;

export default class PlewParser extends Parser {
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
	public static override readonly EOF = Token.EOF;
	public static readonly RULE_function = 0;
	public static readonly RULE_function_declaration = 1;
	public static readonly RULE_return_type = 2;
	public static readonly RULE_arguments = 3;
	public static readonly RULE_argument = 4;
	public static readonly RULE_block = 5;
	public static readonly RULE_statement = 6;
	public static readonly RULE_return_statement = 7;
	public static readonly RULE_expression = 8;
	public static readonly RULE_add = 9;
	public static readonly RULE_multiply = 10;
	public static readonly RULE_unary = 11;
	public static readonly RULE_primary = 12;
	public static readonly RULE_function_name = 13;
	public static readonly RULE_type = 14;
	public static readonly RULE_value = 15;
	public static readonly RULE_literal = 16;
	public static readonly RULE_integer_literal = 17;
	public static readonly RULE_float_literal = 18;
	public static readonly RULE_string_literal = 19;
	public static readonly RULE_bool_literal = 20;
	public static readonly RULE_req_newline = 21;
	public static readonly RULE_opt_newline = 22;
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
	// tslint:disable:no-trailing-whitespace
	public static readonly ruleNames: string[] = [
		"function", "function_declaration", "return_type", "arguments", "argument", 
		"block", "statement", "return_statement", "expression", "add", "multiply", 
		"unary", "primary", "function_name", "type", "value", "literal", "integer_literal", 
		"float_literal", "string_literal", "bool_literal", "req_newline", "opt_newline",
	];
	public get grammarFileName(): string { return "Plew.g4"; }
	public get literalNames(): (string | null)[] { return PlewParser.literalNames; }
	public get symbolicNames(): (string | null)[] { return PlewParser.symbolicNames; }
	public get ruleNames(): string[] { return PlewParser.ruleNames; }
	public get serializedATN(): number[] { return PlewParser._serializedATN; }

	protected createFailedPredicateException(predicate?: string, message?: string): FailedPredicateException {
		return new FailedPredicateException(this, predicate, message);
	}

	constructor(input: TokenStream) {
		super(input);
		this._interp = new ParserATNSimulator(this, PlewParser._ATN, PlewParser.DecisionsToDFA, new PredictionContextCache());
	}
	// @RuleVersion(0)
	public function_(): FunctionContext {
		let localctx: FunctionContext = new FunctionContext(this, this._ctx, this.state);
		this.enterRule(localctx, 0, PlewParser.RULE_function);
		try {
			this.enterOuterAlt(localctx, 1);
			{
			this.state = 46;
			this.function_declaration();
			this.state = 47;
			this.block();
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return localctx;
	}
	// @RuleVersion(0)
	public function_declaration(): Function_declarationContext {
		let localctx: Function_declarationContext = new Function_declarationContext(this, this._ctx, this.state);
		this.enterRule(localctx, 2, PlewParser.RULE_function_declaration);
		let _la: number;
		try {
			this.enterOuterAlt(localctx, 1);
			{
			this.state = 49;
			this.match(PlewParser.T__0);
			this.state = 50;
			this.function_name();
			this.state = 51;
			this.match(PlewParser.T__1);
			this.state = 53;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			if (_la===16) {
				{
				this.state = 52;
				this.arguments();
				}
			}

			this.state = 55;
			this.match(PlewParser.T__2);
			this.state = 57;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			if (_la===4) {
				{
				this.state = 56;
				this.return_type();
				}
			}

			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return localctx;
	}
	// @RuleVersion(0)
	public return_type(): Return_typeContext {
		let localctx: Return_typeContext = new Return_typeContext(this, this._ctx, this.state);
		this.enterRule(localctx, 4, PlewParser.RULE_return_type);
		try {
			this.enterOuterAlt(localctx, 1);
			{
			this.state = 59;
			this.match(PlewParser.T__3);
			this.state = 60;
			this.type_();
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return localctx;
	}
	// @RuleVersion(0)
	public arguments(): ArgumentsContext {
		let localctx: ArgumentsContext = new ArgumentsContext(this, this._ctx, this.state);
		this.enterRule(localctx, 6, PlewParser.RULE_arguments);
		let _la: number;
		try {
			this.enterOuterAlt(localctx, 1);
			{
			this.state = 62;
			this.argument();
			this.state = 67;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			while (_la===5) {
				{
				{
				this.state = 63;
				this.match(PlewParser.T__4);
				this.state = 64;
				this.argument();
				}
				}
				this.state = 69;
				this._errHandler.sync(this);
				_la = this._input.LA(1);
			}
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return localctx;
	}
	// @RuleVersion(0)
	public argument(): ArgumentContext {
		let localctx: ArgumentContext = new ArgumentContext(this, this._ctx, this.state);
		this.enterRule(localctx, 8, PlewParser.RULE_argument);
		try {
			this.enterOuterAlt(localctx, 1);
			{
			this.state = 70;
			this.value();
			this.state = 71;
			this.match(PlewParser.T__5);
			this.state = 72;
			this.type_();
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return localctx;
	}
	// @RuleVersion(0)
	public block(): BlockContext {
		let localctx: BlockContext = new BlockContext(this, this._ctx, this.state);
		this.enterRule(localctx, 10, PlewParser.RULE_block);
		let _la: number;
		try {
			this.enterOuterAlt(localctx, 1);
			{
			this.state = 74;
			this.match(PlewParser.T__6);
			this.state = 76;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			if (_la===14) {
				{
				this.state = 75;
				this.match(PlewParser.NEWLINE);
				}
			}

			this.state = 81;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			while ((((_la) & ~0x1F) === 0 && ((1 << _la) & 1161220) !== 0)) {
				{
				{
				this.state = 78;
				this.statement();
				}
				}
				this.state = 83;
				this._errHandler.sync(this);
				_la = this._input.LA(1);
			}
			this.state = 84;
			this.match(PlewParser.T__7);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return localctx;
	}
	// @RuleVersion(0)
	public statement(): StatementContext {
		let localctx: StatementContext = new StatementContext(this, this._ctx, this.state);
		this.enterRule(localctx, 12, PlewParser.RULE_statement);
		try {
			this.enterOuterAlt(localctx, 1);
			{
			this.state = 86;
			this.expression();
			this.state = 87;
			this.match(PlewParser.NEWLINE);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return localctx;
	}
	// @RuleVersion(0)
	public return_statement(): Return_statementContext {
		let localctx: Return_statementContext = new Return_statementContext(this, this._ctx, this.state);
		this.enterRule(localctx, 14, PlewParser.RULE_return_statement);
		try {
			this.enterOuterAlt(localctx, 1);
			{
			this.state = 89;
			this.match(PlewParser.T__8);
			this.state = 90;
			this.expression();
			this.state = 91;
			this.match(PlewParser.NEWLINE);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return localctx;
	}
	// @RuleVersion(0)
	public expression(): ExpressionContext {
		let localctx: ExpressionContext = new ExpressionContext(this, this._ctx, this.state);
		this.enterRule(localctx, 16, PlewParser.RULE_expression);
		try {
			this.enterOuterAlt(localctx, 1);
			{
			this.state = 93;
			this.add(0);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return localctx;
	}

	public add(): AddContext;
	public add(_p: number): AddContext;
	// @RuleVersion(0)
	public add(_p?: number): AddContext {
		if (_p === undefined) {
			_p = 0;
		}

		let _parentctx: ParserRuleContext = this._ctx;
		let _parentState: number = this.state;
		let localctx: AddContext = new AddContext(this, this._ctx, _parentState);
		let _prevctx: AddContext = localctx;
		let _startState: number = 18;
		this.enterRecursionRule(localctx, 18, PlewParser.RULE_add, _p);
		try {
			let _alt: number;
			this.enterOuterAlt(localctx, 1);
			{
			{
			this.state = 96;
			this.multiply(0);
			}
			this._ctx.stop = this._input.LT(-1);
			this.state = 105;
			this._errHandler.sync(this);
			_alt = this._interp.adaptivePredict(this._input, 5, this._ctx);
			while (_alt !== 2 && _alt !== ATN.INVALID_ALT_NUMBER) {
				if (_alt === 1) {
					if (this._parseListeners != null) {
						this.triggerExitRuleEvent();
					}
					_prevctx = localctx;
					{
					{
					localctx = new AddContext(this, _parentctx, _parentState);
					this.pushNewRecursionContext(localctx, _startState, PlewParser.RULE_add);
					this.state = 98;
					if (!(this.precpred(this._ctx, 2))) {
						throw this.createFailedPredicateException("this.precpred(this._ctx, 2)");
					}
					this.state = 99;
					this.match(PlewParser.ADD_OP);
					this.state = 100;
					this.opt_newline();
					this.state = 101;
					this.multiply(0);
					}
					}
				}
				this.state = 107;
				this._errHandler.sync(this);
				_alt = this._interp.adaptivePredict(this._input, 5, this._ctx);
			}
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.unrollRecursionContexts(_parentctx);
		}
		return localctx;
	}

	public multiply(): MultiplyContext;
	public multiply(_p: number): MultiplyContext;
	// @RuleVersion(0)
	public multiply(_p?: number): MultiplyContext {
		if (_p === undefined) {
			_p = 0;
		}

		let _parentctx: ParserRuleContext = this._ctx;
		let _parentState: number = this.state;
		let localctx: MultiplyContext = new MultiplyContext(this, this._ctx, _parentState);
		let _prevctx: MultiplyContext = localctx;
		let _startState: number = 20;
		this.enterRecursionRule(localctx, 20, PlewParser.RULE_multiply, _p);
		try {
			let _alt: number;
			this.enterOuterAlt(localctx, 1);
			{
			{
			this.state = 109;
			this.unary();
			}
			this._ctx.stop = this._input.LT(-1);
			this.state = 118;
			this._errHandler.sync(this);
			_alt = this._interp.adaptivePredict(this._input, 6, this._ctx);
			while (_alt !== 2 && _alt !== ATN.INVALID_ALT_NUMBER) {
				if (_alt === 1) {
					if (this._parseListeners != null) {
						this.triggerExitRuleEvent();
					}
					_prevctx = localctx;
					{
					{
					localctx = new MultiplyContext(this, _parentctx, _parentState);
					this.pushNewRecursionContext(localctx, _startState, PlewParser.RULE_multiply);
					this.state = 111;
					if (!(this.precpred(this._ctx, 2))) {
						throw this.createFailedPredicateException("this.precpred(this._ctx, 2)");
					}
					this.state = 112;
					this.match(PlewParser.MUL_OP);
					this.state = 113;
					this.opt_newline();
					this.state = 114;
					this.unary();
					}
					}
				}
				this.state = 120;
				this._errHandler.sync(this);
				_alt = this._interp.adaptivePredict(this._input, 6, this._ctx);
			}
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.unrollRecursionContexts(_parentctx);
		}
		return localctx;
	}
	// @RuleVersion(0)
	public unary(): UnaryContext {
		let localctx: UnaryContext = new UnaryContext(this, this._ctx, this.state);
		this.enterRule(localctx, 22, PlewParser.RULE_unary);
		let _la: number;
		try {
			this.enterOuterAlt(localctx, 1);
			{
			this.state = 122;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			if (_la===20) {
				{
				this.state = 121;
				this.match(PlewParser.UNARY_OP);
				}
			}

			this.state = 124;
			this.primary();
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return localctx;
	}
	// @RuleVersion(0)
	public primary(): PrimaryContext {
		let localctx: PrimaryContext = new PrimaryContext(this, this._ctx, this.state);
		this.enterRule(localctx, 24, PlewParser.RULE_primary);
		try {
			this.state = 132;
			this._errHandler.sync(this);
			switch (this._input.LA(1)) {
			case 11:
			case 12:
			case 13:
			case 15:
				this.enterOuterAlt(localctx, 1);
				{
				this.state = 126;
				this.literal();
				}
				break;
			case 16:
				this.enterOuterAlt(localctx, 2);
				{
				this.state = 127;
				this.value();
				}
				break;
			case 2:
				this.enterOuterAlt(localctx, 3);
				{
				this.state = 128;
				this.match(PlewParser.T__1);
				this.state = 129;
				this.expression();
				this.state = 130;
				this.match(PlewParser.T__2);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return localctx;
	}
	// @RuleVersion(0)
	public function_name(): Function_nameContext {
		let localctx: Function_nameContext = new Function_nameContext(this, this._ctx, this.state);
		this.enterRule(localctx, 26, PlewParser.RULE_function_name);
		try {
			this.enterOuterAlt(localctx, 1);
			{
			this.state = 134;
			this.match(PlewParser.SNAKE_CASE);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return localctx;
	}
	// @RuleVersion(0)
	public type_(): TypeContext {
		let localctx: TypeContext = new TypeContext(this, this._ctx, this.state);
		this.enterRule(localctx, 28, PlewParser.RULE_type);
		try {
			this.enterOuterAlt(localctx, 1);
			{
			this.state = 136;
			this.match(PlewParser.PASCAL_CASE);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return localctx;
	}
	// @RuleVersion(0)
	public value(): ValueContext {
		let localctx: ValueContext = new ValueContext(this, this._ctx, this.state);
		this.enterRule(localctx, 30, PlewParser.RULE_value);
		try {
			this.enterOuterAlt(localctx, 1);
			{
			this.state = 138;
			this.match(PlewParser.SNAKE_CASE);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return localctx;
	}
	// @RuleVersion(0)
	public literal(): LiteralContext {
		let localctx: LiteralContext = new LiteralContext(this, this._ctx, this.state);
		this.enterRule(localctx, 32, PlewParser.RULE_literal);
		try {
			this.state = 144;
			this._errHandler.sync(this);
			switch ( this._interp.adaptivePredict(this._input, 9, this._ctx) ) {
			case 1:
				this.enterOuterAlt(localctx, 1);
				{
				this.state = 140;
				this.integer_literal();
				}
				break;
			case 2:
				this.enterOuterAlt(localctx, 2);
				{
				this.state = 141;
				this.float_literal();
				}
				break;
			case 3:
				this.enterOuterAlt(localctx, 3);
				{
				this.state = 142;
				this.string_literal();
				}
				break;
			case 4:
				this.enterOuterAlt(localctx, 4);
				{
				this.state = 143;
				this.bool_literal();
				}
				break;
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return localctx;
	}
	// @RuleVersion(0)
	public integer_literal(): Integer_literalContext {
		let localctx: Integer_literalContext = new Integer_literalContext(this, this._ctx, this.state);
		this.enterRule(localctx, 34, PlewParser.RULE_integer_literal);
		try {
			let _alt: number;
			this.enterOuterAlt(localctx, 1);
			{
			this.state = 147;
			this._errHandler.sync(this);
			_alt = 1;
			do {
				switch (_alt) {
				case 1:
					{
					{
					this.state = 146;
					this.match(PlewParser.DIGIT);
					}
					}
					break;
				default:
					throw new NoViableAltException(this);
				}
				this.state = 149;
				this._errHandler.sync(this);
				_alt = this._interp.adaptivePredict(this._input, 10, this._ctx);
			} while (_alt !== 2 && _alt !== ATN.INVALID_ALT_NUMBER);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return localctx;
	}
	// @RuleVersion(0)
	public float_literal(): Float_literalContext {
		let localctx: Float_literalContext = new Float_literalContext(this, this._ctx, this.state);
		this.enterRule(localctx, 36, PlewParser.RULE_float_literal);
		let _la: number;
		try {
			let _alt: number;
			this.enterOuterAlt(localctx, 1);
			{
			this.state = 152;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			do {
				{
				{
				this.state = 151;
				this.match(PlewParser.DIGIT);
				}
				}
				this.state = 154;
				this._errHandler.sync(this);
				_la = this._input.LA(1);
			} while (_la===15);
			this.state = 156;
			this.match(PlewParser.T__9);
			this.state = 158;
			this._errHandler.sync(this);
			_alt = 1;
			do {
				switch (_alt) {
				case 1:
					{
					{
					this.state = 157;
					this.match(PlewParser.DIGIT);
					}
					}
					break;
				default:
					throw new NoViableAltException(this);
				}
				this.state = 160;
				this._errHandler.sync(this);
				_alt = this._interp.adaptivePredict(this._input, 12, this._ctx);
			} while (_alt !== 2 && _alt !== ATN.INVALID_ALT_NUMBER);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return localctx;
	}
	// @RuleVersion(0)
	public string_literal(): String_literalContext {
		let localctx: String_literalContext = new String_literalContext(this, this._ctx, this.state);
		this.enterRule(localctx, 38, PlewParser.RULE_string_literal);
		try {
			let _alt: number;
			this.enterOuterAlt(localctx, 1);
			{
			this.state = 162;
			this.match(PlewParser.T__10);
			this.state = 166;
			this._errHandler.sync(this);
			_alt = this._interp.adaptivePredict(this._input, 13, this._ctx);
			while (_alt !== 1 && _alt !== ATN.INVALID_ALT_NUMBER) {
				if (_alt === 1 + 1) {
					{
					{
					this.state = 163;
					this.matchWildcard();
					}
					}
				}
				this.state = 168;
				this._errHandler.sync(this);
				_alt = this._interp.adaptivePredict(this._input, 13, this._ctx);
			}
			this.state = 169;
			this.match(PlewParser.T__10);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return localctx;
	}
	// @RuleVersion(0)
	public bool_literal(): Bool_literalContext {
		let localctx: Bool_literalContext = new Bool_literalContext(this, this._ctx, this.state);
		this.enterRule(localctx, 40, PlewParser.RULE_bool_literal);
		let _la: number;
		try {
			this.enterOuterAlt(localctx, 1);
			{
			this.state = 171;
			_la = this._input.LA(1);
			if(!(_la===12 || _la===13)) {
			this._errHandler.recoverInline(this);
			}
			else {
				this._errHandler.reportMatch(this);
			    this.consume();
			}
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return localctx;
	}
	// @RuleVersion(0)
	public req_newline(): Req_newlineContext {
		let localctx: Req_newlineContext = new Req_newlineContext(this, this._ctx, this.state);
		this.enterRule(localctx, 42, PlewParser.RULE_req_newline);
		try {
			this.enterOuterAlt(localctx, 1);
			{
			this.state = 173;
			this.match(PlewParser.NEWLINE);
			this.state = 174;
			this.opt_newline();
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return localctx;
	}
	// @RuleVersion(0)
	public opt_newline(): Opt_newlineContext {
		let localctx: Opt_newlineContext = new Opt_newlineContext(this, this._ctx, this.state);
		this.enterRule(localctx, 44, PlewParser.RULE_opt_newline);
		let _la: number;
		try {
			this.enterOuterAlt(localctx, 1);
			{
			this.state = 179;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			while (_la===14) {
				{
				{
				this.state = 176;
				this.match(PlewParser.NEWLINE);
				}
				}
				this.state = 181;
				this._errHandler.sync(this);
				_la = this._input.LA(1);
			}
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return localctx;
	}

	public sempred(localctx: RuleContext, ruleIndex: number, predIndex: number): boolean {
		switch (ruleIndex) {
		case 9:
			return this.add_sempred(localctx as AddContext, predIndex);
		case 10:
			return this.multiply_sempred(localctx as MultiplyContext, predIndex);
		}
		return true;
	}
	private add_sempred(localctx: AddContext, predIndex: number): boolean {
		switch (predIndex) {
		case 0:
			return this.precpred(this._ctx, 2);
		}
		return true;
	}
	private multiply_sempred(localctx: MultiplyContext, predIndex: number): boolean {
		switch (predIndex) {
		case 1:
			return this.precpred(this._ctx, 2);
		}
		return true;
	}

	public static readonly _serializedATN: number[] = [4,1,20,183,2,0,7,0,2,
	1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,7,7,7,2,8,7,8,2,9,7,9,2,
	10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,14,2,15,7,15,2,16,7,16,2,17,
	7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,21,2,22,7,22,1,0,1,0,1,0,1,1,
	1,1,1,1,1,1,3,1,54,8,1,1,1,1,1,3,1,58,8,1,1,2,1,2,1,2,1,3,1,3,1,3,5,3,66,
	8,3,10,3,12,3,69,9,3,1,4,1,4,1,4,1,4,1,5,1,5,3,5,77,8,5,1,5,5,5,80,8,5,
	10,5,12,5,83,9,5,1,5,1,5,1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,8,1,8,1,9,1,9,1,
	9,1,9,1,9,1,9,1,9,1,9,5,9,104,8,9,10,9,12,9,107,9,9,1,10,1,10,1,10,1,10,
	1,10,1,10,1,10,1,10,5,10,117,8,10,10,10,12,10,120,9,10,1,11,3,11,123,8,
	11,1,11,1,11,1,12,1,12,1,12,1,12,1,12,1,12,3,12,133,8,12,1,13,1,13,1,14,
	1,14,1,15,1,15,1,16,1,16,1,16,1,16,3,16,145,8,16,1,17,4,17,148,8,17,11,
	17,12,17,149,1,18,4,18,153,8,18,11,18,12,18,154,1,18,1,18,4,18,159,8,18,
	11,18,12,18,160,1,19,1,19,5,19,165,8,19,10,19,12,19,168,9,19,1,19,1,19,
	1,20,1,20,1,21,1,21,1,21,1,22,5,22,178,8,22,10,22,12,22,181,9,22,1,22,1,
	166,2,18,20,23,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,
	42,44,0,1,1,0,12,13,177,0,46,1,0,0,0,2,49,1,0,0,0,4,59,1,0,0,0,6,62,1,0,
	0,0,8,70,1,0,0,0,10,74,1,0,0,0,12,86,1,0,0,0,14,89,1,0,0,0,16,93,1,0,0,
	0,18,95,1,0,0,0,20,108,1,0,0,0,22,122,1,0,0,0,24,132,1,0,0,0,26,134,1,0,
	0,0,28,136,1,0,0,0,30,138,1,0,0,0,32,144,1,0,0,0,34,147,1,0,0,0,36,152,
	1,0,0,0,38,162,1,0,0,0,40,171,1,0,0,0,42,173,1,0,0,0,44,179,1,0,0,0,46,
	47,3,2,1,0,47,48,3,10,5,0,48,1,1,0,0,0,49,50,5,1,0,0,50,51,3,26,13,0,51,
	53,5,2,0,0,52,54,3,6,3,0,53,52,1,0,0,0,53,54,1,0,0,0,54,55,1,0,0,0,55,57,
	5,3,0,0,56,58,3,4,2,0,57,56,1,0,0,0,57,58,1,0,0,0,58,3,1,0,0,0,59,60,5,
	4,0,0,60,61,3,28,14,0,61,5,1,0,0,0,62,67,3,8,4,0,63,64,5,5,0,0,64,66,3,
	8,4,0,65,63,1,0,0,0,66,69,1,0,0,0,67,65,1,0,0,0,67,68,1,0,0,0,68,7,1,0,
	0,0,69,67,1,0,0,0,70,71,3,30,15,0,71,72,5,6,0,0,72,73,3,28,14,0,73,9,1,
	0,0,0,74,76,5,7,0,0,75,77,5,14,0,0,76,75,1,0,0,0,76,77,1,0,0,0,77,81,1,
	0,0,0,78,80,3,12,6,0,79,78,1,0,0,0,80,83,1,0,0,0,81,79,1,0,0,0,81,82,1,
	0,0,0,82,84,1,0,0,0,83,81,1,0,0,0,84,85,5,8,0,0,85,11,1,0,0,0,86,87,3,16,
	8,0,87,88,5,14,0,0,88,13,1,0,0,0,89,90,5,9,0,0,90,91,3,16,8,0,91,92,5,14,
	0,0,92,15,1,0,0,0,93,94,3,18,9,0,94,17,1,0,0,0,95,96,6,9,-1,0,96,97,3,20,
	10,0,97,105,1,0,0,0,98,99,10,2,0,0,99,100,5,18,0,0,100,101,3,44,22,0,101,
	102,3,20,10,0,102,104,1,0,0,0,103,98,1,0,0,0,104,107,1,0,0,0,105,103,1,
	0,0,0,105,106,1,0,0,0,106,19,1,0,0,0,107,105,1,0,0,0,108,109,6,10,-1,0,
	109,110,3,22,11,0,110,118,1,0,0,0,111,112,10,2,0,0,112,113,5,19,0,0,113,
	114,3,44,22,0,114,115,3,22,11,0,115,117,1,0,0,0,116,111,1,0,0,0,117,120,
	1,0,0,0,118,116,1,0,0,0,118,119,1,0,0,0,119,21,1,0,0,0,120,118,1,0,0,0,
	121,123,5,20,0,0,122,121,1,0,0,0,122,123,1,0,0,0,123,124,1,0,0,0,124,125,
	3,24,12,0,125,23,1,0,0,0,126,133,3,32,16,0,127,133,3,30,15,0,128,129,5,
	2,0,0,129,130,3,16,8,0,130,131,5,3,0,0,131,133,1,0,0,0,132,126,1,0,0,0,
	132,127,1,0,0,0,132,128,1,0,0,0,133,25,1,0,0,0,134,135,5,16,0,0,135,27,
	1,0,0,0,136,137,5,17,0,0,137,29,1,0,0,0,138,139,5,16,0,0,139,31,1,0,0,0,
	140,145,3,34,17,0,141,145,3,36,18,0,142,145,3,38,19,0,143,145,3,40,20,0,
	144,140,1,0,0,0,144,141,1,0,0,0,144,142,1,0,0,0,144,143,1,0,0,0,145,33,
	1,0,0,0,146,148,5,15,0,0,147,146,1,0,0,0,148,149,1,0,0,0,149,147,1,0,0,
	0,149,150,1,0,0,0,150,35,1,0,0,0,151,153,5,15,0,0,152,151,1,0,0,0,153,154,
	1,0,0,0,154,152,1,0,0,0,154,155,1,0,0,0,155,156,1,0,0,0,156,158,5,10,0,
	0,157,159,5,15,0,0,158,157,1,0,0,0,159,160,1,0,0,0,160,158,1,0,0,0,160,
	161,1,0,0,0,161,37,1,0,0,0,162,166,5,11,0,0,163,165,9,0,0,0,164,163,1,0,
	0,0,165,168,1,0,0,0,166,167,1,0,0,0,166,164,1,0,0,0,167,169,1,0,0,0,168,
	166,1,0,0,0,169,170,5,11,0,0,170,39,1,0,0,0,171,172,7,0,0,0,172,41,1,0,
	0,0,173,174,5,14,0,0,174,175,3,44,22,0,175,43,1,0,0,0,176,178,5,14,0,0,
	177,176,1,0,0,0,178,181,1,0,0,0,179,177,1,0,0,0,179,180,1,0,0,0,180,45,
	1,0,0,0,181,179,1,0,0,0,15,53,57,67,76,81,105,118,122,132,144,149,154,160,
	166,179];

	private static __ATN: ATN;
	public static get _ATN(): ATN {
		if (!PlewParser.__ATN) {
			PlewParser.__ATN = new ATNDeserializer().deserialize(PlewParser._serializedATN);
		}

		return PlewParser.__ATN;
	}


	static DecisionsToDFA = PlewParser._ATN.decisionToState.map( (ds: DecisionState, index: number) => new DFA(ds, index) );

}

export class FunctionContext extends ParserRuleContext {
	constructor(parser?: PlewParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public function_declaration(): Function_declarationContext {
		return this.getTypedRuleContext(Function_declarationContext, 0) as Function_declarationContext;
	}
	public block(): BlockContext {
		return this.getTypedRuleContext(BlockContext, 0) as BlockContext;
	}
    public get ruleIndex(): number {
    	return PlewParser.RULE_function;
	}
	public enterRule(listener: PlewListener): void {
	    if(listener.enterFunction) {
	 		listener.enterFunction(this);
		}
	}
	public exitRule(listener: PlewListener): void {
	    if(listener.exitFunction) {
	 		listener.exitFunction(this);
		}
	}
}


export class Function_declarationContext extends ParserRuleContext {
	constructor(parser?: PlewParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public function_name(): Function_nameContext {
		return this.getTypedRuleContext(Function_nameContext, 0) as Function_nameContext;
	}
	public arguments(): ArgumentsContext {
		return this.getTypedRuleContext(ArgumentsContext, 0) as ArgumentsContext;
	}
	public return_type(): Return_typeContext {
		return this.getTypedRuleContext(Return_typeContext, 0) as Return_typeContext;
	}
    public get ruleIndex(): number {
    	return PlewParser.RULE_function_declaration;
	}
	public enterRule(listener: PlewListener): void {
	    if(listener.enterFunction_declaration) {
	 		listener.enterFunction_declaration(this);
		}
	}
	public exitRule(listener: PlewListener): void {
	    if(listener.exitFunction_declaration) {
	 		listener.exitFunction_declaration(this);
		}
	}
}


export class Return_typeContext extends ParserRuleContext {
	constructor(parser?: PlewParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public type_(): TypeContext {
		return this.getTypedRuleContext(TypeContext, 0) as TypeContext;
	}
    public get ruleIndex(): number {
    	return PlewParser.RULE_return_type;
	}
	public enterRule(listener: PlewListener): void {
	    if(listener.enterReturn_type) {
	 		listener.enterReturn_type(this);
		}
	}
	public exitRule(listener: PlewListener): void {
	    if(listener.exitReturn_type) {
	 		listener.exitReturn_type(this);
		}
	}
}


export class ArgumentsContext extends ParserRuleContext {
	constructor(parser?: PlewParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public argument_list(): ArgumentContext[] {
		return this.getTypedRuleContexts(ArgumentContext) as ArgumentContext[];
	}
	public argument(i: number): ArgumentContext {
		return this.getTypedRuleContext(ArgumentContext, i) as ArgumentContext;
	}
    public get ruleIndex(): number {
    	return PlewParser.RULE_arguments;
	}
	public enterRule(listener: PlewListener): void {
	    if(listener.enterArguments) {
	 		listener.enterArguments(this);
		}
	}
	public exitRule(listener: PlewListener): void {
	    if(listener.exitArguments) {
	 		listener.exitArguments(this);
		}
	}
}


export class ArgumentContext extends ParserRuleContext {
	constructor(parser?: PlewParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public value(): ValueContext {
		return this.getTypedRuleContext(ValueContext, 0) as ValueContext;
	}
	public type_(): TypeContext {
		return this.getTypedRuleContext(TypeContext, 0) as TypeContext;
	}
    public get ruleIndex(): number {
    	return PlewParser.RULE_argument;
	}
	public enterRule(listener: PlewListener): void {
	    if(listener.enterArgument) {
	 		listener.enterArgument(this);
		}
	}
	public exitRule(listener: PlewListener): void {
	    if(listener.exitArgument) {
	 		listener.exitArgument(this);
		}
	}
}


export class BlockContext extends ParserRuleContext {
	constructor(parser?: PlewParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public NEWLINE(): TerminalNode {
		return this.getToken(PlewParser.NEWLINE, 0);
	}
	public statement_list(): StatementContext[] {
		return this.getTypedRuleContexts(StatementContext) as StatementContext[];
	}
	public statement(i: number): StatementContext {
		return this.getTypedRuleContext(StatementContext, i) as StatementContext;
	}
    public get ruleIndex(): number {
    	return PlewParser.RULE_block;
	}
	public enterRule(listener: PlewListener): void {
	    if(listener.enterBlock) {
	 		listener.enterBlock(this);
		}
	}
	public exitRule(listener: PlewListener): void {
	    if(listener.exitBlock) {
	 		listener.exitBlock(this);
		}
	}
}


export class StatementContext extends ParserRuleContext {
	constructor(parser?: PlewParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public expression(): ExpressionContext {
		return this.getTypedRuleContext(ExpressionContext, 0) as ExpressionContext;
	}
	public NEWLINE(): TerminalNode {
		return this.getToken(PlewParser.NEWLINE, 0);
	}
    public get ruleIndex(): number {
    	return PlewParser.RULE_statement;
	}
	public enterRule(listener: PlewListener): void {
	    if(listener.enterStatement) {
	 		listener.enterStatement(this);
		}
	}
	public exitRule(listener: PlewListener): void {
	    if(listener.exitStatement) {
	 		listener.exitStatement(this);
		}
	}
}


export class Return_statementContext extends ParserRuleContext {
	constructor(parser?: PlewParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public expression(): ExpressionContext {
		return this.getTypedRuleContext(ExpressionContext, 0) as ExpressionContext;
	}
	public NEWLINE(): TerminalNode {
		return this.getToken(PlewParser.NEWLINE, 0);
	}
    public get ruleIndex(): number {
    	return PlewParser.RULE_return_statement;
	}
	public enterRule(listener: PlewListener): void {
	    if(listener.enterReturn_statement) {
	 		listener.enterReturn_statement(this);
		}
	}
	public exitRule(listener: PlewListener): void {
	    if(listener.exitReturn_statement) {
	 		listener.exitReturn_statement(this);
		}
	}
}


export class ExpressionContext extends ParserRuleContext {
	constructor(parser?: PlewParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public add(): AddContext {
		return this.getTypedRuleContext(AddContext, 0) as AddContext;
	}
    public get ruleIndex(): number {
    	return PlewParser.RULE_expression;
	}
	public enterRule(listener: PlewListener): void {
	    if(listener.enterExpression) {
	 		listener.enterExpression(this);
		}
	}
	public exitRule(listener: PlewListener): void {
	    if(listener.exitExpression) {
	 		listener.exitExpression(this);
		}
	}
}


export class AddContext extends ParserRuleContext {
	constructor(parser?: PlewParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public multiply(): MultiplyContext {
		return this.getTypedRuleContext(MultiplyContext, 0) as MultiplyContext;
	}
	public add(): AddContext {
		return this.getTypedRuleContext(AddContext, 0) as AddContext;
	}
	public ADD_OP(): TerminalNode {
		return this.getToken(PlewParser.ADD_OP, 0);
	}
	public opt_newline(): Opt_newlineContext {
		return this.getTypedRuleContext(Opt_newlineContext, 0) as Opt_newlineContext;
	}
    public get ruleIndex(): number {
    	return PlewParser.RULE_add;
	}
	public enterRule(listener: PlewListener): void {
	    if(listener.enterAdd) {
	 		listener.enterAdd(this);
		}
	}
	public exitRule(listener: PlewListener): void {
	    if(listener.exitAdd) {
	 		listener.exitAdd(this);
		}
	}
}


export class MultiplyContext extends ParserRuleContext {
	constructor(parser?: PlewParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public unary(): UnaryContext {
		return this.getTypedRuleContext(UnaryContext, 0) as UnaryContext;
	}
	public multiply(): MultiplyContext {
		return this.getTypedRuleContext(MultiplyContext, 0) as MultiplyContext;
	}
	public MUL_OP(): TerminalNode {
		return this.getToken(PlewParser.MUL_OP, 0);
	}
	public opt_newline(): Opt_newlineContext {
		return this.getTypedRuleContext(Opt_newlineContext, 0) as Opt_newlineContext;
	}
    public get ruleIndex(): number {
    	return PlewParser.RULE_multiply;
	}
	public enterRule(listener: PlewListener): void {
	    if(listener.enterMultiply) {
	 		listener.enterMultiply(this);
		}
	}
	public exitRule(listener: PlewListener): void {
	    if(listener.exitMultiply) {
	 		listener.exitMultiply(this);
		}
	}
}


export class UnaryContext extends ParserRuleContext {
	constructor(parser?: PlewParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public primary(): PrimaryContext {
		return this.getTypedRuleContext(PrimaryContext, 0) as PrimaryContext;
	}
	public UNARY_OP(): TerminalNode {
		return this.getToken(PlewParser.UNARY_OP, 0);
	}
    public get ruleIndex(): number {
    	return PlewParser.RULE_unary;
	}
	public enterRule(listener: PlewListener): void {
	    if(listener.enterUnary) {
	 		listener.enterUnary(this);
		}
	}
	public exitRule(listener: PlewListener): void {
	    if(listener.exitUnary) {
	 		listener.exitUnary(this);
		}
	}
}


export class PrimaryContext extends ParserRuleContext {
	constructor(parser?: PlewParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public literal(): LiteralContext {
		return this.getTypedRuleContext(LiteralContext, 0) as LiteralContext;
	}
	public value(): ValueContext {
		return this.getTypedRuleContext(ValueContext, 0) as ValueContext;
	}
	public expression(): ExpressionContext {
		return this.getTypedRuleContext(ExpressionContext, 0) as ExpressionContext;
	}
    public get ruleIndex(): number {
    	return PlewParser.RULE_primary;
	}
	public enterRule(listener: PlewListener): void {
	    if(listener.enterPrimary) {
	 		listener.enterPrimary(this);
		}
	}
	public exitRule(listener: PlewListener): void {
	    if(listener.exitPrimary) {
	 		listener.exitPrimary(this);
		}
	}
}


export class Function_nameContext extends ParserRuleContext {
	constructor(parser?: PlewParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public SNAKE_CASE(): TerminalNode {
		return this.getToken(PlewParser.SNAKE_CASE, 0);
	}
    public get ruleIndex(): number {
    	return PlewParser.RULE_function_name;
	}
	public enterRule(listener: PlewListener): void {
	    if(listener.enterFunction_name) {
	 		listener.enterFunction_name(this);
		}
	}
	public exitRule(listener: PlewListener): void {
	    if(listener.exitFunction_name) {
	 		listener.exitFunction_name(this);
		}
	}
}


export class TypeContext extends ParserRuleContext {
	constructor(parser?: PlewParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public PASCAL_CASE(): TerminalNode {
		return this.getToken(PlewParser.PASCAL_CASE, 0);
	}
    public get ruleIndex(): number {
    	return PlewParser.RULE_type;
	}
	public enterRule(listener: PlewListener): void {
	    if(listener.enterType) {
	 		listener.enterType(this);
		}
	}
	public exitRule(listener: PlewListener): void {
	    if(listener.exitType) {
	 		listener.exitType(this);
		}
	}
}


export class ValueContext extends ParserRuleContext {
	constructor(parser?: PlewParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public SNAKE_CASE(): TerminalNode {
		return this.getToken(PlewParser.SNAKE_CASE, 0);
	}
    public get ruleIndex(): number {
    	return PlewParser.RULE_value;
	}
	public enterRule(listener: PlewListener): void {
	    if(listener.enterValue) {
	 		listener.enterValue(this);
		}
	}
	public exitRule(listener: PlewListener): void {
	    if(listener.exitValue) {
	 		listener.exitValue(this);
		}
	}
}


export class LiteralContext extends ParserRuleContext {
	constructor(parser?: PlewParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public integer_literal(): Integer_literalContext {
		return this.getTypedRuleContext(Integer_literalContext, 0) as Integer_literalContext;
	}
	public float_literal(): Float_literalContext {
		return this.getTypedRuleContext(Float_literalContext, 0) as Float_literalContext;
	}
	public string_literal(): String_literalContext {
		return this.getTypedRuleContext(String_literalContext, 0) as String_literalContext;
	}
	public bool_literal(): Bool_literalContext {
		return this.getTypedRuleContext(Bool_literalContext, 0) as Bool_literalContext;
	}
    public get ruleIndex(): number {
    	return PlewParser.RULE_literal;
	}
	public enterRule(listener: PlewListener): void {
	    if(listener.enterLiteral) {
	 		listener.enterLiteral(this);
		}
	}
	public exitRule(listener: PlewListener): void {
	    if(listener.exitLiteral) {
	 		listener.exitLiteral(this);
		}
	}
}


export class Integer_literalContext extends ParserRuleContext {
	constructor(parser?: PlewParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public DIGIT_list(): TerminalNode[] {
	    	return this.getTokens(PlewParser.DIGIT);
	}
	public DIGIT(i: number): TerminalNode {
		return this.getToken(PlewParser.DIGIT, i);
	}
    public get ruleIndex(): number {
    	return PlewParser.RULE_integer_literal;
	}
	public enterRule(listener: PlewListener): void {
	    if(listener.enterInteger_literal) {
	 		listener.enterInteger_literal(this);
		}
	}
	public exitRule(listener: PlewListener): void {
	    if(listener.exitInteger_literal) {
	 		listener.exitInteger_literal(this);
		}
	}
}


export class Float_literalContext extends ParserRuleContext {
	constructor(parser?: PlewParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public DIGIT_list(): TerminalNode[] {
	    	return this.getTokens(PlewParser.DIGIT);
	}
	public DIGIT(i: number): TerminalNode {
		return this.getToken(PlewParser.DIGIT, i);
	}
    public get ruleIndex(): number {
    	return PlewParser.RULE_float_literal;
	}
	public enterRule(listener: PlewListener): void {
	    if(listener.enterFloat_literal) {
	 		listener.enterFloat_literal(this);
		}
	}
	public exitRule(listener: PlewListener): void {
	    if(listener.exitFloat_literal) {
	 		listener.exitFloat_literal(this);
		}
	}
}


export class String_literalContext extends ParserRuleContext {
	constructor(parser?: PlewParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
    public get ruleIndex(): number {
    	return PlewParser.RULE_string_literal;
	}
	public enterRule(listener: PlewListener): void {
	    if(listener.enterString_literal) {
	 		listener.enterString_literal(this);
		}
	}
	public exitRule(listener: PlewListener): void {
	    if(listener.exitString_literal) {
	 		listener.exitString_literal(this);
		}
	}
}


export class Bool_literalContext extends ParserRuleContext {
	constructor(parser?: PlewParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
    public get ruleIndex(): number {
    	return PlewParser.RULE_bool_literal;
	}
	public enterRule(listener: PlewListener): void {
	    if(listener.enterBool_literal) {
	 		listener.enterBool_literal(this);
		}
	}
	public exitRule(listener: PlewListener): void {
	    if(listener.exitBool_literal) {
	 		listener.exitBool_literal(this);
		}
	}
}


export class Req_newlineContext extends ParserRuleContext {
	constructor(parser?: PlewParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public NEWLINE(): TerminalNode {
		return this.getToken(PlewParser.NEWLINE, 0);
	}
	public opt_newline(): Opt_newlineContext {
		return this.getTypedRuleContext(Opt_newlineContext, 0) as Opt_newlineContext;
	}
    public get ruleIndex(): number {
    	return PlewParser.RULE_req_newline;
	}
	public enterRule(listener: PlewListener): void {
	    if(listener.enterReq_newline) {
	 		listener.enterReq_newline(this);
		}
	}
	public exitRule(listener: PlewListener): void {
	    if(listener.exitReq_newline) {
	 		listener.exitReq_newline(this);
		}
	}
}


export class Opt_newlineContext extends ParserRuleContext {
	constructor(parser?: PlewParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public NEWLINE_list(): TerminalNode[] {
	    	return this.getTokens(PlewParser.NEWLINE);
	}
	public NEWLINE(i: number): TerminalNode {
		return this.getToken(PlewParser.NEWLINE, i);
	}
    public get ruleIndex(): number {
    	return PlewParser.RULE_opt_newline;
	}
	public enterRule(listener: PlewListener): void {
	    if(listener.enterOpt_newline) {
	 		listener.enterOpt_newline(this);
		}
	}
	public exitRule(listener: PlewListener): void {
	    if(listener.exitOpt_newline) {
	 		listener.exitOpt_newline(this);
		}
	}
}
