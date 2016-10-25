using UnityEngine;
using System.Collections;
using System.Globalization;

public class nodes : MonoBehaviour {
    string file_path="testVerts";
   public GameObject node;

    // Use this for initialization
    void Start () {

        // Read the file and display it line by line.
            System.IO.StreamReader file = new System.IO.StreamReader(file_path);

            while (!file.EndOfStream)
            {
            string[] s = file.ReadLine().Split(' ');


                 float space1=int.Parse(s[0], CultureInfo.InvariantCulture);

                float space2 = int.Parse(s[1], CultureInfo.InvariantCulture);

            float space3 = int.Parse(s[2], CultureInfo.InvariantCulture);
            Instantiate(node, new Vector3(space1, space2, space3),Quaternion.EulerAngles(0,0,0),transform);
                // Do Something with the input. 
            }

            file.Close();

          }

    // Update is called once per frame
    void Update () {
	
	}
}
