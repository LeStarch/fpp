port P
passive component C1 {
  output port pOut: [4] P
  output port serialOut: serial
}
passive component C2 {
  sync input port pIn: P
  sync input port serialIn: serial
}
instance c1: C1 base id 0x100
instance c2: C2 base id 0x200
topology T {
  connections C {
    c1.pOut -> c2.pIn
    c1.serialOut -> c2.pIn
    c1.pOut -> c2.serialIn
    c1.serialOut -> c2.serialIn
  }
}
