# MyCLisp
This is a Data Structures and Algorithms project based on building a Lisp like programming language using C. This implementation is inspired from the book Build Your Own Lisp by Daniel Holden and uses an open source parser combinator library called mpc.

## This is a brief summary / list of things this lisp supports : 
(Copied from Capabilities File)

1. Decimal number handling  
2. Textual operator handling (not, or, and, nil, true, false, etc)
3. Made Code Library installation independent
4. Error Reporting
5. Comparison Operators, Logical Operators (def {x y} {10 20} ; if (== x y) {+ x y} {- x y}), Arithmetic Operators
6. % operator handling
7. Can Demonstrate Metaprogramming
8. File Loading Support
9. Function Evaluation Supporting Partial Evaluation :
	Ex :
		def {add-mul} (\ {x y} {+ x (* x y)})
		add-mul 10 20
			210
		add-mul 10
			(\ {y} {+ x (* x y)})
		def {add-mul-ten} (add-mul 10)
		add-mul-ten 50
			510
	
	Variadic Functions : Using & which returns a QExpression : fun {myhead f & args} {head args}
			
10. Q Expressions - Similar to Macros in Conventional Lisps
11. S Expressions - Code Data Interchange
12. Fundamental Operations - For QExprs(defined in main code):
	a.list - Converts S expression to Q expression
	b.head - Accepts single argument, a non empty q expression, returns first element
	c.tail - Accepts single argument, a non empty q expression, returns everything except first element
	d.join - joins 2 Q-expressions into one Q-expression
	e.eval - COnverts Qexpr to S-Expression and evaluates it
		* Demo:
				MyCLisp>list 1 2 3 4
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
				3
13. Variables (Using def / =)
14. Functions :
	Defined using \ (lambda)
	Takes one or more sized list as arglist
	Eg :
		\ {x y} {+ x y}
		(\ {x y} {+ x y}) 10 20
		def {add-together} (\ {x y} {+ x y})
		add-together 10 20

15. Independant Standard library support with the functions :
	a. fun - A function for defining functions (Without using explicit lambda exprs) - fun {add-together x y} {+ x y}
	b. unpack / curry - A function which adds the passed function to the beginning of a list passed as second argument hence allowing us to use functions which require variable arguments with lists. (unpack + {1 2 3})
	c.pack / uncurry - A function to use functions that take as input lists with variable arguments instead.
	d.len, reverse -rev list, do- perform actions in order, let - opens a new scope
		let and do can be used in conjunction to define local variables. Eg : let {do (= {x} 100) (x)} ; x.
	e. flip - flips evaluation order ((flip def) 1 {x}), comp - used for composition
	f. List functions - nth (nth item in list), take, drop, split, elem
	g. map (map - {5 6 7 8 2 22 44}), filter (filter (\ {x} {> x 2}) {5 2 11 -7 8 1}), foldl
	h. select - similar to switch case, case - same as switch case.
