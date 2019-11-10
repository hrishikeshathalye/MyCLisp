# MyCLisp
This is a Data Structures and Algorithms project based on building a Lisp like programming language using C. This implementation is inspired from the book Build Your Own Lisp by Daniel Holden and uses an open source parser combinator library called mpc. Lisps are a very powerful category of programming languages which can demonstrate homoiconicity viz. Code-Data Interchange. Mainly using recursion and meta programming, Lisps can shorten complex programs to a few lines of codes.
For more details and exact specification of lisps in common practice (such as Clojure, Common Lisp, etc) have a look here : 
1. https://en.wikipedia.org/wiki/Lisp_(programming_language)
2. https://twobithistory.org/2018/10/14/lisp.html

I have learnt a lot over the course of this project and would encourage anyone even slightly interested to take it up. There are a lot of improvements such as garbage collection, lexical scoping, etc possible on this implementation which I will also be trying to implement in due course. Moreover, studying lisp also provides insight into the thinking behind the initial phases of AI development and Lisp still remains a popular choice for the same purpose.

## This is a brief summary / list of things this lisp supports : 
(Copied from Capabilities File)

1. Decimal number handling  
2. Textual operator handling (not, or, and, nil, add, sub, etc)
3. Made Code Library installation independent
4. Error Reporting
5. Comparison Operators, Logical Operators (def {x y} {10 20} ; if (== x y) {+ x y} {- x y}), Arithmetic Operators
6. % operator handling
7. Can Demonstrate Metaprogramming
8. File Loading Support
9. Function Evaluation Supporting Partial Evaluation :
	
	<b>Ex :</b>
		
		def {add-mul} (\ {x y} {+ x (* x y)})
		add-mul 10 20
			210
		add-mul 10
			(\ {y} {+ x (* x y)})
		def {add-mul-ten} (add-mul 10)
		add-mul-ten 50
			510
			
	Variadic Functions : Using & which returns a QExpression : 
		
		fun {myhead f & args} {head args}
			
10. Q Expressions - Similar to Macros in Conventional Lisps
11. S Expressions - Code Data Interchange
12. Fundamental Operations - For QExprs(defined in main code):
	* list - Converts S expression to Q expression
	* head - Accepts single argument, a non empty q expression, returns first element
	* tail - Accepts single argument, a non empty q expression, returns everything except first element
	* join - joins 2 Q-expressions into one Q-expression
	* eval - Converts Qexpr to S-Expression and evaluates it
		
		<b>Demo:</b>
				<pre>MyCLisp>list 1 2 3 4
				{1 2 3 4}
				MyCLisp> {head (list 1 2 3 4)}
				{head (list 1 2 3 4)}
				MyCLisp> eval {head (list 1 2 3 4)}
				{1}
				MyCLisp> tail {tail tail tail}
				{tail tail}
				MyCLisp> eval (tail {tail tail {5 6 7}})
				{6 7}
				MyCLisp> eval (head {(+ 1 2) (+ 10 20)})
				3</pre>
13. Variables (Using def / =)
14. Functions :
	Defined using \ (lambda)
	Takes one or more sized list as arglist.
	<br><b>Eg :</b>
		
		\ {x y} {+ x y}
		(\ {x y} {+ x y}) 10 20
		def {add-together} (\ {x y} {+ x y})
		add-together 10 20

15. Independant Standard library support with the functions :
	* fun - A function for defining functions (Without using explicit lambda exprs) 
			
		fun {add-together x y} {+ x y}
	
	* unpack / curry - A function which adds the passed function to the beginning of a list passed as second argument hence allowing us to use functions which require variable arguments with lists. 
			
		unpack + {1 2 3})
	
	* pack / uncurry - A function to use functions that take as input lists with variable arguments instead.
	
	* len, reverse -rev list, do- perform actions in order, let - opens a new scope.
	Let and do can be used in conjunction to define local variables. 
	<br><b>Eg :</b> 
	
		let {do (= {x} 100) (x)} ; x.
	* flip - flips evaluation order ((flip def) 1 {x}), comp - used for composition
	* List functions - nth (nth item in list), take, drop, split, elem
	* map (map - {5 6 7 8 2 22 44}), filter (filter (\ {x} {> x 2}) {5 2 11 -7 8 1}), foldl
	* select - similar to switch case, case - same as switch case.
