import * as fs from "node:fs";
import { CharStream, CommonTokenStream } from "antlr4";
import PlewLexer from "./grammer/PlewLexer";
import PlewParser from "./grammer/PlewParser";

const mainCode = fs.readFileSync("./examples/main.pw", "utf-8");

const chars = new CharStream(mainCode);
const lexer = new PlewLexer(chars);
const tokens = new CommonTokenStream(lexer);
const parser = new PlewParser(tokens);
const tree = parser.function_();

console.log("Parse tree:", tree.toStringTree(null, parser));
