xof 0303txt 0032

Frame Root {
  FrameTransformMatrix {
     1.000000, 0.000000, 0.000000, 0.000000,
     0.000000,-0.000000, 1.000000, 0.000000,
     0.000000, 1.000000, 0.000000, 0.000000,
     0.000000, 0.000000, 0.000000, 1.000000;;
  }
  Frame Concrete {
    FrameTransformMatrix {
      100.000000, 0.000000, 0.000000, 0.000000,
       0.000000, 0.500000, 0.000000, 0.000000,
       0.000000, 0.000000, 0.500000, 0.000000,
      43.507713,67.355797,-2.903388, 1.000000;;
    }
    Mesh { // Concrete mesh
      18;
      -1.563529;-700.214355;20.919935;,
       0.727477;-700.214355;20.919935;,
      -1.563529;-223.314285;20.919935;,
       0.727477;-223.314285;20.919935;,
      -1.521589;-215.892502;-22.280066;,
       0.727477;-215.892502;-22.280066;,
       1.115000;-223.314285;20.919935;,
       1.186311;-215.892502;-22.280066;,
      -1.852921;-700.214355;20.919935;,
      -1.852921;-223.314285;20.919935;,
      -1.903260;-215.892502;-22.280066;,
      -3.090012;-700.214355;20.919935;,
      -3.090012;-223.314285;20.919935;,
      -3.140351;-215.892502;-22.280066;,
       1.115001;-700.214355;20.919935;,
       2.164138;-223.314285;20.919935;,
       2.235449;-215.892502;-22.280066;,
       2.164139;-700.214355;20.919935;;
      10;
      4;2,3,1,0;,
      4;4,5,3,2;,
      4;8,9,2,0;,
      4;12,13,10,9;,
      4;11,12,9,8;,
      4;1,3,6,14;,
      4;15,17,14,6;,
      4;16,15,6,7;,
      4;9,10,4,2;,
      4;7,6,3,5;;
      MeshNormals { // Concrete normals
        10;
         0.000000; 0.000000; 1.000000;,
         0.000000; 0.985561; 0.169320;,
        -0.000000; 0.000000; 1.000000;,
         0.000000; 0.985561; 0.169320;,
        -0.000000; 0.000000; 1.000000;,
        -0.000000; 0.000000; 1.000000;,
         0.000000; 0.000000; 1.000000;,
         0.000000; 0.985561; 0.169320;,
         0.000000; 0.985561; 0.169320;,
         0.000000; 0.985561; 0.169320;;
        10;
        4;0,0,0,0;,
        4;1,1,1,1;,
        4;2,2,2,2;,
        4;3,3,3,3;,
        4;4,4,4,4;,
        4;5,5,5,5;,
        4;6,6,6,6;,
        4;7,7,7,7;,
        4;8,8,8,8;,
        4;9,9,9,9;;
      } // End of Concrete normals
      MeshMaterialList { // Concrete material list
        2;
        10;
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0;
        Material concrete {
           0.640000; 0.640000; 0.640000; 1.000000;;
           96.078431;
           0.500000; 0.500000; 0.500000;;
           0.000000; 0.000000; 0.000000;;
          TextureFilename {"�R���N��.jpeg";}
        }
        Material Clear {
           0.640000; 0.640000; 0.640000; 0.000000;;
           96.078431;
           0.000000; 0.000000; 0.000000;;
           0.000000; 0.000000; 0.000000;;
        }
      } // End of Concrete material list
    } // End of Concrete mesh
  } // End of Concrete
} // End of Root
