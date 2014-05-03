function K = Hintersection(A, B)
I = size(A,1); 
J = size(B,1); 
K = zeros(I, J);

for i = 1:I
    for j= 1:J
        K(i,j) = sum(min(A(i,:),B(j,:)));
    end
end
end
