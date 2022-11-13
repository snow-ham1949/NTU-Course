`ifndef ADDERS
`define ADDERS
`include "gates.v"

// half adder, gate level modeling
module HA(output C, S, input A, B);
	XOR g0(S, A, B);
	AND g1(C, A, B);
endmodule

// full adder, gate level modeling
module FA(output CO, S, input A, B, CI);
	wire c0, s0, c1, s1;
	HA ha0(c0, s0, A, B);
	HA ha1(c1, s1, s0, CI);
	assign S = s1;
	OR or0(CO, c0, c1);
endmodule

// adder without delay, register-transfer level modeling
module adder_rtl(
	output C3,       // carry output
	output[2:0] S,   // sum
	input[2:0] A, B, // operands
	input C0         // carry input
	);
	assign {C3, S} = A+B+C0;
endmodule

//  ripple-carry adder, gate level modeling
//  Do not modify the input/output of module
module rca_gl(
	output C3,       // carry output
	output[2:0] S,   // sum
	input[2:0] A, B, // operands
	input C0         // carry input
	);

	// TODO:: Implement gate-level RCA
	wire C1, C2;
	wire S_0, S_1, S_2;
	FA fa0(C1, S_0, A[0], B[0], C0);
	FA fa1(C2, S_1, A[1], B[1], C1);
	FA fa2(C3, S_2, A[2], B[2], C2);
	
	assign S = {S_2, S_1, S_0};
endmodule

// carry-lookahead adder, gate level modeling
// Do not modify the input/output of module
module cla_gl(
	output C3,       // carry output
	output[2:0] S,   // sum
	input[2:0] A, B, // operands
	input C0         // carry input
	);

	// TODO:: Implement gate-level CLA
	wire [3:0] G, P;
	
	AND G_0(G[0], A[0], B[0]);
	AND G_1(G[1], A[1], B[1]);
	AND G_2(G[2], A[2], B[2]);
	
	OR P_0(P[0], A[0], B[0]);
	OR P_1(P[1], A[1], B[1]);
	OR P_2(P[2], A[2], B[2]);

	wire G1P2, G0P1P2, C0P0P1P2;
	AND g1p2(G1P2, G[1], P[2]);
	AND4 g0p1p2(G0P1P2, G[0], P[1], P[2], 1'b1);
	AND4 c0p0p1p2(C0P0P1P2, C0, P[0], P[1], P[2]);
	OR4 c3(C3, G[2], G1P2, G0P1P2, C0P0P1P2);

	wire P0C0, C1;
	AND p0c0(P0C0, P[0], C0);
	OR c1(C1, G[0], P0C0);

	wire G0P1, C0P0P1, C2;
	AND g0p1(G0P1, G[0], P[1]);
	AND4 c0p0p1(C0P0P1, C0, P[0], P[1], 1'b1);
	OR4 c2(C2, G[1], G0P1, C0P0P1, 1'b0);

	wire S_0, S_1, S_2;
	wire _C3, _C2, _C1;
	FA fa2(_C3, S_2, A[2], B[2], C2);
	FA fa1(_C2, S_1, A[1], B[1], C1);
	FA fa0(_C1, S_0, A[0], B[0], C0);
	
	assign S = {S_2, S_1, S_0};

endmodule

`endif
