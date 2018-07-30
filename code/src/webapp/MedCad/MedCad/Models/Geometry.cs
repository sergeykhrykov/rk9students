using Newtonsoft.Json;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace MedCad.Models
{
    public class Geometry
    {
        [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
        [JsonIgnore]
        public int GeometryId { get; set; }

        public string JsonMeshRepresentation { get; set; }

        public int Version { get; set; }

        public string CreatedAt { get; set; }
       
        [JsonIgnore]
        public virtual Model Model { get; set; }

        //[ForeignKey("Model")]
        [JsonIgnore]
        public int ModelId { get; set; }
    }
}
