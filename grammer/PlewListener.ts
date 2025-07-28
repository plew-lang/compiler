// Generated from ./grammer/Plew.g4 by ANTLR 4.13.2

import {ParseTreeListener} from "antlr4";


import { FunctionContext } from "./PlewParser.js";
import { Function_declarationContext } from "./PlewParser.js";
import { Return_typeContext } from "./PlewParser.js";
import { ArgumentsContext } from "./PlewParser.js";
import { ArgumentContext } from "./PlewParser.js";
import { BlockContext } from "./PlewParser.js";
import { StatementContext } from "./PlewParser.js";
import { Return_statementContext } from "./PlewParser.js";
import { ExpressionContext } from "./PlewParser.js";
import { AddContext } from "./PlewParser.js";
import { MultiplyContext } from "./PlewParser.js";
import { UnaryContext } from "./PlewParser.js";
import { PrimaryContext } from "./PlewParser.js";
import { Function_nameContext } from "./PlewParser.js";
import { TypeContext } from "./PlewParser.js";
import { ValueContext } from "./PlewParser.js";
import { LiteralContext } from "./PlewParser.js";
import { Integer_literalContext } from "./PlewParser.js";
import { Float_literalContext } from "./PlewParser.js";
import { String_literalContext } from "./PlewParser.js";
import { Bool_literalContext } from "./PlewParser.js";
import { Req_newlineContext } from "./PlewParser.js";
import { Opt_newlineContext } from "./PlewParser.js";


/**
 * This interface defines a complete listener for a parse tree produced by
 * `PlewParser`.
 */
export default class PlewListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by `PlewParser.function`.
	 * @param ctx the parse tree
	 */
	enterFunction?: (ctx: FunctionContext) => void;
	/**
	 * Exit a parse tree produced by `PlewParser.function`.
	 * @param ctx the parse tree
	 */
	exitFunction?: (ctx: FunctionContext) => void;
	/**
	 * Enter a parse tree produced by `PlewParser.function_declaration`.
	 * @param ctx the parse tree
	 */
	enterFunction_declaration?: (ctx: Function_declarationContext) => void;
	/**
	 * Exit a parse tree produced by `PlewParser.function_declaration`.
	 * @param ctx the parse tree
	 */
	exitFunction_declaration?: (ctx: Function_declarationContext) => void;
	/**
	 * Enter a parse tree produced by `PlewParser.return_type`.
	 * @param ctx the parse tree
	 */
	enterReturn_type?: (ctx: Return_typeContext) => void;
	/**
	 * Exit a parse tree produced by `PlewParser.return_type`.
	 * @param ctx the parse tree
	 */
	exitReturn_type?: (ctx: Return_typeContext) => void;
	/**
	 * Enter a parse tree produced by `PlewParser.arguments`.
	 * @param ctx the parse tree
	 */
	enterArguments?: (ctx: ArgumentsContext) => void;
	/**
	 * Exit a parse tree produced by `PlewParser.arguments`.
	 * @param ctx the parse tree
	 */
	exitArguments?: (ctx: ArgumentsContext) => void;
	/**
	 * Enter a parse tree produced by `PlewParser.argument`.
	 * @param ctx the parse tree
	 */
	enterArgument?: (ctx: ArgumentContext) => void;
	/**
	 * Exit a parse tree produced by `PlewParser.argument`.
	 * @param ctx the parse tree
	 */
	exitArgument?: (ctx: ArgumentContext) => void;
	/**
	 * Enter a parse tree produced by `PlewParser.block`.
	 * @param ctx the parse tree
	 */
	enterBlock?: (ctx: BlockContext) => void;
	/**
	 * Exit a parse tree produced by `PlewParser.block`.
	 * @param ctx the parse tree
	 */
	exitBlock?: (ctx: BlockContext) => void;
	/**
	 * Enter a parse tree produced by `PlewParser.statement`.
	 * @param ctx the parse tree
	 */
	enterStatement?: (ctx: StatementContext) => void;
	/**
	 * Exit a parse tree produced by `PlewParser.statement`.
	 * @param ctx the parse tree
	 */
	exitStatement?: (ctx: StatementContext) => void;
	/**
	 * Enter a parse tree produced by `PlewParser.return_statement`.
	 * @param ctx the parse tree
	 */
	enterReturn_statement?: (ctx: Return_statementContext) => void;
	/**
	 * Exit a parse tree produced by `PlewParser.return_statement`.
	 * @param ctx the parse tree
	 */
	exitReturn_statement?: (ctx: Return_statementContext) => void;
	/**
	 * Enter a parse tree produced by `PlewParser.expression`.
	 * @param ctx the parse tree
	 */
	enterExpression?: (ctx: ExpressionContext) => void;
	/**
	 * Exit a parse tree produced by `PlewParser.expression`.
	 * @param ctx the parse tree
	 */
	exitExpression?: (ctx: ExpressionContext) => void;
	/**
	 * Enter a parse tree produced by `PlewParser.add`.
	 * @param ctx the parse tree
	 */
	enterAdd?: (ctx: AddContext) => void;
	/**
	 * Exit a parse tree produced by `PlewParser.add`.
	 * @param ctx the parse tree
	 */
	exitAdd?: (ctx: AddContext) => void;
	/**
	 * Enter a parse tree produced by `PlewParser.multiply`.
	 * @param ctx the parse tree
	 */
	enterMultiply?: (ctx: MultiplyContext) => void;
	/**
	 * Exit a parse tree produced by `PlewParser.multiply`.
	 * @param ctx the parse tree
	 */
	exitMultiply?: (ctx: MultiplyContext) => void;
	/**
	 * Enter a parse tree produced by `PlewParser.unary`.
	 * @param ctx the parse tree
	 */
	enterUnary?: (ctx: UnaryContext) => void;
	/**
	 * Exit a parse tree produced by `PlewParser.unary`.
	 * @param ctx the parse tree
	 */
	exitUnary?: (ctx: UnaryContext) => void;
	/**
	 * Enter a parse tree produced by `PlewParser.primary`.
	 * @param ctx the parse tree
	 */
	enterPrimary?: (ctx: PrimaryContext) => void;
	/**
	 * Exit a parse tree produced by `PlewParser.primary`.
	 * @param ctx the parse tree
	 */
	exitPrimary?: (ctx: PrimaryContext) => void;
	/**
	 * Enter a parse tree produced by `PlewParser.function_name`.
	 * @param ctx the parse tree
	 */
	enterFunction_name?: (ctx: Function_nameContext) => void;
	/**
	 * Exit a parse tree produced by `PlewParser.function_name`.
	 * @param ctx the parse tree
	 */
	exitFunction_name?: (ctx: Function_nameContext) => void;
	/**
	 * Enter a parse tree produced by `PlewParser.type`.
	 * @param ctx the parse tree
	 */
	enterType?: (ctx: TypeContext) => void;
	/**
	 * Exit a parse tree produced by `PlewParser.type`.
	 * @param ctx the parse tree
	 */
	exitType?: (ctx: TypeContext) => void;
	/**
	 * Enter a parse tree produced by `PlewParser.value`.
	 * @param ctx the parse tree
	 */
	enterValue?: (ctx: ValueContext) => void;
	/**
	 * Exit a parse tree produced by `PlewParser.value`.
	 * @param ctx the parse tree
	 */
	exitValue?: (ctx: ValueContext) => void;
	/**
	 * Enter a parse tree produced by `PlewParser.literal`.
	 * @param ctx the parse tree
	 */
	enterLiteral?: (ctx: LiteralContext) => void;
	/**
	 * Exit a parse tree produced by `PlewParser.literal`.
	 * @param ctx the parse tree
	 */
	exitLiteral?: (ctx: LiteralContext) => void;
	/**
	 * Enter a parse tree produced by `PlewParser.integer_literal`.
	 * @param ctx the parse tree
	 */
	enterInteger_literal?: (ctx: Integer_literalContext) => void;
	/**
	 * Exit a parse tree produced by `PlewParser.integer_literal`.
	 * @param ctx the parse tree
	 */
	exitInteger_literal?: (ctx: Integer_literalContext) => void;
	/**
	 * Enter a parse tree produced by `PlewParser.float_literal`.
	 * @param ctx the parse tree
	 */
	enterFloat_literal?: (ctx: Float_literalContext) => void;
	/**
	 * Exit a parse tree produced by `PlewParser.float_literal`.
	 * @param ctx the parse tree
	 */
	exitFloat_literal?: (ctx: Float_literalContext) => void;
	/**
	 * Enter a parse tree produced by `PlewParser.string_literal`.
	 * @param ctx the parse tree
	 */
	enterString_literal?: (ctx: String_literalContext) => void;
	/**
	 * Exit a parse tree produced by `PlewParser.string_literal`.
	 * @param ctx the parse tree
	 */
	exitString_literal?: (ctx: String_literalContext) => void;
	/**
	 * Enter a parse tree produced by `PlewParser.bool_literal`.
	 * @param ctx the parse tree
	 */
	enterBool_literal?: (ctx: Bool_literalContext) => void;
	/**
	 * Exit a parse tree produced by `PlewParser.bool_literal`.
	 * @param ctx the parse tree
	 */
	exitBool_literal?: (ctx: Bool_literalContext) => void;
	/**
	 * Enter a parse tree produced by `PlewParser.req_newline`.
	 * @param ctx the parse tree
	 */
	enterReq_newline?: (ctx: Req_newlineContext) => void;
	/**
	 * Exit a parse tree produced by `PlewParser.req_newline`.
	 * @param ctx the parse tree
	 */
	exitReq_newline?: (ctx: Req_newlineContext) => void;
	/**
	 * Enter a parse tree produced by `PlewParser.opt_newline`.
	 * @param ctx the parse tree
	 */
	enterOpt_newline?: (ctx: Opt_newlineContext) => void;
	/**
	 * Exit a parse tree produced by `PlewParser.opt_newline`.
	 * @param ctx the parse tree
	 */
	exitOpt_newline?: (ctx: Opt_newlineContext) => void;
}

